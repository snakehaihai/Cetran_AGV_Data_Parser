#ifndef IMAGEMESSAGE_H
#define IMAGEMESSAGE_H

#include <cereal/types/polymorphic.hpp>
#include <opencv2/opencv.hpp>

#include "Message.h"

namespace cereal_log
{

class ImageMessage : public Message
{
    friend class cereal::access;

    template <class Archive, cereal::traits::DisableIf<cereal::traits::is_text_archive<Archive>::value> = cereal::traits::sfinae>
	void save(Archive& ar) const;

	template <class Archive, cereal::traits::DisableIf<cereal::traits::is_text_archive<Archive>::value> = cereal::traits::sfinae>
	void load(Archive& ar);

public:
    typedef std::shared_ptr<ImageMessage> Ptr;

    ImageMessage(void);

    ImageMessage& operator=(const ImageMessage& message);

    // Disable copy operator.
    ImageMessage(const ImageMessage&) = delete;

    std::string encoding;
    cv::Mat image;
    unsigned long long seq;
    unsigned int exposureTime_us;
    unsigned int gain_dB;
}; // ImageMessage

template <class Archive, cereal::traits::DisableIf<cereal::traits::is_text_archive<Archive>::value>>
void
ImageMessage::save(Archive& ar) const
{
	ar(cereal::base_class<Message>(this));

	ar(encoding);

	size_t elemSize = image.elemSize();
	int elemType = image.type();

	ar(image.cols);
	ar(image.rows);
	ar(elemSize);
	ar(elemType);

	const size_t dataSize = image.cols * image.rows * elemSize;
	ar(cereal::binary_data(image.ptr(), dataSize));

	ar(seq);
	ar(exposureTime_us);
	ar(gain_dB);
}

template <class Archive, cereal::traits::DisableIf<cereal::traits::is_text_archive<Archive>::value>>
void
ImageMessage::load(Archive& ar)
{
	ar(cereal::base_class<Message>(this));

	ar(encoding);

	int cols, rows;
	size_t elemSize;
	int elemType;

	ar(cols);
	ar(rows);
	ar(elemSize);
	ar(elemType);

	if (image.empty() ||
		image.rows != rows ||
		image.cols != cols ||
		image.type() != elemType)
	{
		image.create(rows, cols, elemType);
	}

	const size_t dataSize = cols * rows * elemSize;
	ar(cereal::binary_data(image.ptr(), dataSize));

	ar(seq);
	ar(exposureTime_us);
	ar(gain_dB);
}

} // namespace cereal_log

#include <cereal/archives/portable_binary.hpp>

CEREAL_REGISTER_TYPE(cereal_log::ImageMessage);
CEREAL_SPECIALIZE_FOR_ARCHIVE(cereal::PortableBinaryInputArchive, cereal_log::ImageMessage, cereal::specialization::member_load_save);
CEREAL_SPECIALIZE_FOR_ARCHIVE(cereal::PortableBinaryOutputArchive, cereal_log::ImageMessage, cereal::specialization::member_load_save);

#endif
