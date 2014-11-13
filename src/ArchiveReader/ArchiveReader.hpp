/*
 * ArchiveReader.hpp
 *
 *  Created on: Nov 6, 2014
 *      Author: Oleksii Ozerov
 */

#ifndef ARCHIVEREADER_HPP_
#define ARCHIVEREADER_HPP_

#include "../Header/HeaderReader/HeaderReader.hpp"
#include "../Header/Header.hpp"
#include "ArchiveReaderException.hpp"

#include <string>
#include <fstream>
#include <vector>

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

    HeaderReader m_HeaderReader;

    std::vector<Header> m_HeaderCollection;
};
}



#endif /* ARCHIVEREADER_HPP_ */
