#include "ImageMessage.h"

#include <cereal/types/polymorphic.hpp>

namespace cereal_log
{

ImageMessage::ImageMessage(void)
    : Message(0)
{

}

ImageMessage&
ImageMessage::operator=(const ImageMessage& message)
{
    if (&message == this)
    {
        return *this;
    }

    encoding = message.encoding;
    message.image.copyTo(image);
    timeStamp = message.timeStamp;
    seq = message.seq;
    exposureTime_us = message.exposureTime_us;
    gain_dB = message.gain_dB;

    return *this;
}

} // namespace cereal_log
