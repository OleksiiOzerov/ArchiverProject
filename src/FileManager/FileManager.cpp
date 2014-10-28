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

std::vector<std::string> FileManager::GetAllFiles() const
{
     std::vector<std::string> allRecursiveFiles;

     for (auto & filePath : m_RootFilesCollection)
     {
         if (boost::filesystem::is_regular_file(filePath))
         {
             allRecursiveFiles.push_back(filePath.string());
         }
         else if (boost::filesystem::is_directory(filePath))
         {
             allRecursiveFiles.push_back(filePath.string());

             for (boost::filesystem::recursive_directory_iterator fileIterator(filePath);
                  fileIterator != boost::filesystem::recursive_directory_iterator();
                  ++fileIterator)
             {

                 allRecursiveFiles.push_back( fileIterator->path().string());
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

               // if (fileIterator.level() > 1)
            //    {
            //        fileIterator.pop();
            //    }
                //else
                {
                    for (int i = 0; i <= fileIterator.level(); ++i)
                    {
                        std::cout << "-";
                    }

                    std::cout << fileIterator->path() << std::endl;
//
//                    if (boost::filesystem::is_regular_file(fileIterator->path()))
//                    {
//                    }
                }
            }
        }
    }
}
}

