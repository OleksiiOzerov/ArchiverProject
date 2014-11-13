/*
 * FileProperties.hpp
 *
 *  Created on: Nov 1, 2014
 *      Author: Oleksii Ozerov
 */

#ifndef FILEPROPERTIES_HPP_
#define FILEPROPERTIES_HPP_

#include <boost/filesystem.hpp>

#include <string>
#include <ctime>
#include <iostream>

namespace Archiver
{
class FileProperties
{
public:

    FileProperties(const std::string& fileName);

    void SetFileName(const std::string& fileName);

    const std::string& GetFileName()const;

    void SetFileType(boost::filesystem::file_type fileType);

    boost::filesystem::file_type GetFileType()const;

    void SetFilePermissions(boost::filesystem::perms filePermissions);

    boost::filesystem::perms GetFilePermissions() const;

    void SetFileSize(uintmax_t fileSize);

    uintmax_t GetFileSize() const;

    void SetFileModificationTime(std::time_t modificationTime);

    std::time_t GetFileModificationTime() const;

    friend std::ostream& operator<<(std::ostream& os, FileProperties file);

private:

    std::string m_FileName;

    boost::filesystem::file_type m_FileType;

    boost::filesystem::perms m_FilePermissions;

    uintmax_t m_FileSize;

    std::time_t m_LastMoficationTime;
};
}

#endif /* FILEPROPERTIES_HPP_ */
