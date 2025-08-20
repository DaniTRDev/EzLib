#include "OutLogBuffers/FileOutLogBuffer.h"

FileOutLogBuffer::FileOutLogBuffer(std::filesystem::path path) : m_path(path)
{
}

FileOutLogBuffer::~FileOutLogBuffer()
{
    m_fileStream.close();
}

bool FileOutLogBuffer::close()
{
    m_fileStream.close();
    return true;
}

bool FileOutLogBuffer::open()
{
    m_fileStream.open(m_path, std::ios::out | std::ios::trunc);
    return m_fileStream.is_open() && m_fileStream.good();
}

bool FileOutLogBuffer::opened() const
{
    return m_fileStream.is_open();
}

bool FileOutLogBuffer::write(LogMessage message)
{
    if (!opened())
        return false;
    
    std::string str = message.getRawMessage() + "\n";
    m_fileStream.write(str.data(), str.size());
    m_fileStream.flush();
    
    return m_fileStream.good();
}
