/*
 * FileProperties.cpp
 *
 *  Created on: Nov 1, 2014
 *      Author: Oleksii Ozerov
 */

#include "FileProperties.hpp"

#include <iomanip>

namespace Archiver
{
FileProperties::FileProperties(const std::string& fileName) : m_FileName(fileName),
                                                       m_FileType(boost::filesystem::type_unknown),
                                                       m_FilePermissions(boost::filesystem::perms_not_known),
                                                       m_FileSize(0),
                                                       m_LastMoficationTime(0)
{
}

void FileProperties::SetFileName(const std::string& fileName)
{
    m_FileName = fileName;
}

const std::string& FileProperties::GetFileName()const
{
    return m_FileName;
}

void FileProperties::SetFileType(boost::filesystem::file_type fileType)
{
    m_FileType = fileType;
}

boost::filesystem::file_type FileProperties::GetFileType()const
{
    return m_FileType;
}

void FileProperties::SetFilePermissions(boost::filesystem::perms filePermissions)
{
    m_FilePermissions = filePermissions;
}

boost::filesystem::perms FileProperties::GetFilePermissions() const
{
    return m_FilePermissions;
}

void FileProperties::SetFileSize(uintmax_t fileSize)
{
    m_FileSize = fileSize;
}

uintmax_t FileProperties::GetFileSize() const
{
    return m_FileSize;
}

void FileProperties::SetFileModificationTime(std::time_t modificationTime)
{
    m_LastMoficationTime = modificationTime;
}

std::time_t FileProperties::GetFileModificationTime() const
{
    return m_LastMoficationTime;
}

std::ostream& operator<<(std::ostream& os, FileProperties file)
{
    os << "File name: " << file.m_FileName << std::endl;
    os << "     type: " << file.m_FileType << std::endl;
    os << std::setbase(8);
    os << "     permissions: " << file.m_FilePermissions << std::endl;
    os << std::setbase(10);
    os << "     size: " << file.m_FileSize << std::endl;
    os << "     modification time: " << file.m_LastMoficationTime << std::endl;
    return os;
}

}
