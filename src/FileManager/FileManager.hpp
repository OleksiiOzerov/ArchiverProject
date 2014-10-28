/*
 * FileManager.hpp
 *
 *  Created on: Oct 26, 2014
 *      Author: Oleksii Ozerov
 */

#ifndef FILEMANAGER_HPP_
#define FILEMANAGER_HPP_

#include "FileManagerException.hpp"

#include <boost/filesystem.hpp>

#include <string>
#include <vector>
#include <iterator>
#include <iostream>

namespace Archiver
{
class FileManager
{
public:


    FileManager(std::vector<std::string>& fileNames);

    std::vector<std::string> GetAllFiles() const;

    void PrintAllFiles() const;

private:

    std::vector<boost::filesystem::path> m_RootFilesCollection;

    //std::vector<boost::filesystem::path>::iterator m_CurrentFile;


};
}




#endif /* FILEMANAGER_HPP_ */
