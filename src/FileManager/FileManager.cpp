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

FileManager::FileManager(std::vector<std::string>& inputFileNames)
{
    if (!inputFileNames.empty())
    {
        m_RootFilesCollection.reserve(inputFileNames.size());

        boost::filesystem::path filePath;
        for (const auto & fileName : inputFileNames)
        {
            filePath = fileName;
            if (boost::filesystem::exists(filePath))
            {
                m_RootFilesCollection.push_back(std::move(filePath));
            }
        }
        if (m_RootFilesCollection.empty())
        {
            throw FileManagerException(NO_EXISTING_FILE_ERROR);
        }
    }
    else
    {
        throw FileManagerException(EMPTY_INPUT_ERROR);
    }
}

FileProperties FileManager::SetFileProperties(const boost::filesystem::path& filePath) const
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

std::vector<FileProperties> FileManager::GetAllFiles() const
{
     std::vector<FileProperties> allRecursiveFiles;

     for (auto & filePath : m_RootFilesCollection)
     {
         if (boost::filesystem::is_regular_file(filePath))
         {
             allRecursiveFiles.push_back(SetFileProperties(filePath));
         }
         else if (boost::filesystem::is_directory(filePath))
         {
             allRecursiveFiles.push_back(SetFileProperties(filePath));

             for (boost::filesystem::recursive_directory_iterator fileIterator(filePath);
                  fileIterator != boost::filesystem::recursive_directory_iterator();
                  ++fileIterator)
             {

                 allRecursiveFiles.push_back(SetFileProperties(fileIterator->path()));
             }
         }
     }

     return allRecursiveFiles;
}


void FileManager::PrintAllFiles() const
{
    std::cout << "All " << m_RootFilesCollection.size() <<" files:" << std::endl;

    for (auto & filePath : m_RootFilesCollection)
    {
        if (boost::filesystem::is_regular_file(filePath))
        {
            std::cout << "File: " << filePath << std::endl;
        }
        else if (boost::filesystem::is_directory(filePath))
        {
            std::cout << "Directory: " << filePath << std::endl;

            for (boost::filesystem::recursive_directory_iterator fileIterator(filePath);
                 fileIterator != boost::filesystem::recursive_directory_iterator();
                 ++fileIterator)
            {

                {
                    for (int i = 0; i <= fileIterator.level(); ++i)
                    {
                        std::cout << "-";
                    }

                    std::cout << fileIterator->path() << std::endl;
                }
            }
        }
    }
}
}

