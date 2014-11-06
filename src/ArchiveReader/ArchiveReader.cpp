/*
 * ArchiveReader.cpp
 *
 *  Created on: Nov 6, 2014
 *      Author: Oleksii Ozerov
 */

#include "ArchiveReader.hpp"
#include "ArchiveReaderException.hpp"
namespace Archiver
{
ArchiveReader::ArchiveReader(const std::string& archiveName) : m_ArchiveName(archiveName),
        m_ArchiveFile(archiveName, std::ifstream::in | std::ifstream::binary)
{
    if(!m_ArchiveFile.is_open())
        throw ArchiveReaderException();
}

void ArchiveReader::ReadAllHeaders()
{

    std::string header(BlockSize, '\0');
    m_ArchiveFile.read(&header[0], BlockSize);


}

}


