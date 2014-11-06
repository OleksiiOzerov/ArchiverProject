/*
 * ArchiveReader.hpp
 *
 *  Created on: Nov 6, 2014
 *      Author: Oleksii Ozerov
 */

#ifndef ARCHIVEREADER_HPP_
#define ARCHIVEREADER_HPP_

#include <string>
#include <fstream>

namespace Archiver
{
class ArchiveReader
{
public:

    ArchiveReader(const std::string& archiveName);

    void ReadAllHeaders();

private:

    static const int BlockSize = 512;

    std::string m_ArchiveName;

    std::ifstream m_ArchiveFile;
};
}



#endif /* ARCHIVEREADER_HPP_ */
