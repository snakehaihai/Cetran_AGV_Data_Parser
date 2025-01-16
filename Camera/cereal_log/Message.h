#ifndef MESSAGE_H
#define MESSAGE_H

#include <memory>

#include "TimeStamp.h"

namespace cereal_log
{

class Message
{
	friend class cereal::access;

	template <class Archive>
	void serialize(Archive& ar);

public:
    typedef std::shared_ptr<Message> Ptr;
	
	explicit Message(int64_t id);
    virtual ~Message(void) = 0;

    // Disable copy and assignment operators.
    Message(const Message&) = delete;
    Message& operator=(const Message&) = delete;

	int64_t id;
    TimeStamp timeStamp;
}; // Message

template <class Archive>
void
Message::serialize(Archive& ar)
{
	ar(id, timeStamp);
}

} // namespace cereal_log

#endif
