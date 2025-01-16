#include "LogReader.h"

#include <cereal/archives/portable_binary.hpp>
#include <cereal/types/memory.hpp>
#include <cereal/types/string.hpp>

namespace cereal_log
{

LogReader::LogReader(void)
{

}

bool
LogReader::openLog(const std::string& filename)
{
    if (m_ifs.is_open())
    {
        return false;
    }

    m_ifs.open(filename, std::ios::binary | std::ios::in);

    if (!m_ifs.is_open())
    {
        return false;
    }

    // Find the length of the log file.
    m_ifsEnd = m_ifs.seekg(0, m_ifs.end).tellg();
    m_ifs.seekg(0, m_ifs.beg);

    m_ia = std::make_shared<cereal::PortableBinaryInputArchive>(m_ifs);

    return true;
}

bool
LogReader::read(std::string& topic, Message::Ptr& msg)
{
	std::unique_ptr<Message> pMsg;

    try
    {
        (*m_ia)(topic, pMsg);
    }
    catch (const cereal::Exception&)
    {
        return false;
    }

	msg = std::move(pMsg);

    return true;
}

bool
LogReader::eof(void)
{
    return (m_ifs.tellg() == m_ifsEnd);
}

bool
LogReader::closeLog(void)
{
    if (!m_ifs.is_open())
    {
        return false;
    }

    m_ifs.close();

    return true;
}

} // namespace cereal_log
