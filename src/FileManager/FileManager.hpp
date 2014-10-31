/*
 * FileManager.hpp
 *
 *  Created on: Oct 26, 2014
 *      Author: Oleksii Ozerov
 */

#ifndef FILEMANAGER_HPP_
#define FILEMANAGER_HPP_

#include "FileManagerException.hpp"

#include "FileProperties/FileProperties.hpp"

#include <boost/filesystem.hpp>

#include <string>
#include <vector>
#include <iterator>


namespace Archiver
{
class FileManager
{
public:

    FileManager(std::vector<std::string>& fileNames);

    std::vector<FileProperties> GetAllFiles() const;

    void PrintAllFiles() const;

private:

    FileProperties SetFileProperties(const boost::filesystem::path& filePath) const;

    std::vector<boost::filesystem::path> m_RootFilesCollection;

};
}

#endif /* FILEMANAGER_HPP_ */
