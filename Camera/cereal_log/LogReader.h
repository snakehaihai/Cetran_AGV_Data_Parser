#ifndef LOGREADER_H
#define LOGREADER_H

#include <fstream>

#include "Message.h"

// forward declaration
namespace cereal
{
class PortableBinaryInputArchive;
}

namespace cereal_log
{

class LogReader
{
public:
	explicit LogReader(void);

	bool openLog(const std::string& filename);
    
	bool read(std::string& topic, Message::Ptr& msg);

	bool eof(void);

	bool closeLog(void);

private:
    std::ifstream m_ifs;
    std::shared_ptr<cereal::PortableBinaryInputArchive> m_ia;
    std::streampos m_ifsEnd;
};

} // namespace cereal_log

#endif
