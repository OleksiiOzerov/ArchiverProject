/*
 * FileManager.cpp
 *
 *  Created on: Oct 26, 2014
 *      Author: Oleksii Ozerov
 */

#include "FileManager.hpp"

#include <algorithm>
#include <iostream>

namespace Archiver
{

FileManager::FileManager(const std::vector<std::string>& inputFileNames)
{
    if (!inputFileNames.empty())
    {
        m_InputFilesCollection.reserve(inputFileNames.size());

        boost::filesystem::path filePath;
        for (const auto & fileName : inputFileNames)
        {
            filePath = fileName;
            if (boost::filesystem::exists(filePath))
            {
                m_InputFilesCollection.push_back(std::move(filePath));
            }
        }
        if (m_InputFilesCollection.empty())
        {
            throw FileManagerException(NO_EXISTING_FILE_ERROR);
        }
    }
    else
    {
        throw FileManagerException(EMPTY_INPUT_ERROR);
    }
}

FileProperties FileManager::GetFileProperties(const boost::filesystem::path& filePath) const
{
    FileProperties fileProperties(filePath.string());

    boost::filesystem::file_status fileStatus = status(filePath);

    fileProperties.SetFileType(fileStatus.type());

    fileProperties.SetFilePermissions(fileStatus.permissions());

    if (fileProperties.GetFileType() == boost::filesystem::regular_file)
    {
        fileProperties.SetFileSize(boost::filesystem::file_size(filePath));
    }

    fileProperties.SetFileModificationTime(boost::filesystem::last_write_time(filePath));

    return fileProperties;
}

std::vector<FileProperties> FileManager::GetAllFilesRecursively() const
{
     std::vector<FileProperties> allRecursiveFiles;

     for (auto & filePath : m_InputFilesCollection)
     {
         if (boost::filesystem::is_regular_file(filePath))
         {
             allRecursiveFiles.push_back(GetFileProperties(filePath));
         }
         else if (boost::filesystem::is_directory(filePath))
         {
             allRecursiveFiles.push_back(GetFileProperties(filePath));

             for (boost::filesystem::recursive_directory_iterator fileIterator(filePath);
                  fileIterator != boost::filesystem::recursive_directory_iterator();
                  ++fileIterator)
             {
                 allRecursiveFiles.push_back(GetFileProperties(fileIterator->path()));
             }
         }
     }

     return allRecursiveFiles;
}

}

