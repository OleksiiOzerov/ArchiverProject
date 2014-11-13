/*
 * ArchiveReader.cpp
 *
 *  Created on: Nov 6, 2014
 *      Author: Oleksii Ozerov
 */

#include "ArchiveReader.hpp"

#include "../Header/HeaderReader/HeaderReaderException.hpp"

#include <iomanip>

namespace Archiver
{
ArchiveReader::ArchiveReader(const std::string& archiveName) : m_ArchiveName(archiveName)
{
    if (m_ArchiveName.empty())
        throw ArchiveReaderException(EMPTY_ARCHIVE_NAME);

    m_ArchiveFile.open(m_ArchiveName, std::ifstream::in | std::ifstream::binary);

    if (!m_ArchiveFile.is_open())
        throw ArchiveReaderException(FILE_OPEN_ERROR);
}

void ArchiveReader::ReadAllHeaders()
{
    std::string headerString(BlockSize, '\0');
    m_ArchiveFile.read(&headerString[0], BlockSize);

    try
    {
        while (m_HeaderReader.ReadHeader(headerString) && m_ArchiveFile)
        {
            m_HeaderCollection.push_back(m_HeaderReader.GetHeader());

            m_ArchiveFile.seekg(m_HeaderReader.GetNextHeaderPosition());

            m_ArchiveFile.read(&headerString[0], BlockSize);
        }
    }
    catch(const HeaderReaderException& headerReaderException)
    {
        std::cout << "HeaderReaderException " << std::endl;
        std::cout << headerReaderException.what() << std::endl;
    }

    for (auto fileHeader : m_HeaderCollection)
    {
        std::cout << std::endl;
        std::cout << "File name: " << fileHeader.GetFileName() << std::endl;
        std::cout << "File type: " << fileHeader.GetFileType() << std::endl;
        std::cout << std::setbase(8);
        std::cout << "File permissions: " << fileHeader.GetFilePermissions() << std::endl;
        std::cout << std::setbase(10);
        std::cout << "File size: " << fileHeader.GetFileSize() << std::endl;
        std::cout << "File start pos: " << fileHeader.GetFileStartPosition() << std::endl;
        std::cout << "File end pos: " << fileHeader.GetFileEndPosition() << std::endl;
    }

    std::cout << " All " << m_HeaderCollection.size() << " headers was read" << std::endl;

}

}


