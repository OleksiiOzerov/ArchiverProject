/*
 * FileManager.hpp
 *
 *  Created on: Oct 26, 2014
 *      Author: Oleksii Ozerov
 */

#ifndef FILEMANAGER_HPP_
#define FILEMANAGER_HPP_

#include <boost/filesystem.hpp>

#include <string>
#include <vector>

namespace Archiver
{
class FileManager
{
public:

    FileManager(std::vector<std::string>& fileNames);

    void PrintAllFiles() const;

private:

    std::vector<boost::filesystem::path> m_AllRootFiles;

};
}


#endif /* FILEMANAGER_HPP_ */
