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

FileManager::FileManager(std::vector<std::string>& fileNames)
{
    if (!fileNames.empty())
    {
        m_AllRootFiles.reserve(fileNames.size());
        boost::filesystem::path filePath;
        for (auto iterator = fileNames.begin(); iterator != fileNames.end(); ++iterator)
        {
            filePath = *iterator;
            if (boost::filesystem::exists(filePath))
            {
                m_AllRootFiles.push_back(std::move(filePath));
            }
        }
    }
    else
    {


    }


}


void FileManager::PrintAllFiles() const
{
    std::cout << "All " << m_AllRootFiles.size() <<" files:" << std::endl;

    for (auto & filePath : m_AllRootFiles)
    {
        if (boost::filesystem::is_regular_file(filePath))
        {
            std::cout << "File: " << filePath << std::endl;
        }
        else if (boost::filesystem::is_directory(filePath))
        {
            std::cout << "Directory: " << filePath << std::endl;

            for (boost::filesystem::recursive_directory_iterator it (filePath);
                 it != boost::filesystem::recursive_directory_iterator();
                 ++it)
            {

                if (it.level() > 1)
                {
                    it.pop();
                }
                else
                {
                    for (int i = 0; i <= it.level(); ++i)
                    {
                        std::cout << "-";
                    }

                    std::cout << it->path() << std::endl;
                }
            }
        }
    }
}

}

