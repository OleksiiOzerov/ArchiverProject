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
void ArchiveReader::WriteAllFiles()
{
    std::sort(m_HeaderCollection.begin(),m_HeaderCollection.end(), [](const Header& firstHeader, const Header& secondHeader)
    {
        if (firstHeader.GetFileType() != secondHeader.GetFileType())
        {
            return secondHeader.GetFileType() != boost::filesystem::directory_file;
        }
        else
        {
            const std::string& firstFileName = firstHeader.GetFileName();
            int firstDirectoryLevel = std::count(firstFileName.begin(), firstFileName.end(), '/');

            const std::string& secondFileName = secondHeader.GetFileName();
            int secondDirectoryLevel = std::count(secondFileName .begin(), secondFileName .end(), '/');

            return firstDirectoryLevel < secondDirectoryLevel;
        }
    });

    std::ofstream file;
    std::string fileContent;
    for (auto fileHeader : m_HeaderCollection)
    {
        if (fileHeader.GetFileType() == boost::filesystem::directory_file)
            boost::filesystem::create_directory(fileHeader.GetFileName());
        else if (fileHeader.GetFileType() == boost::filesystem::regular_file)
        {
            file.open(fileHeader.GetFileName(), std::ios::out | std::ios::trunc | std::ios::binary);

            m_ArchiveFile.seekg(fileHeader.GetFileStartPosition());

            fileContent.resize(fileHeader.GetFileEndPosition() - fileHeader.GetFileStartPosition());

            m_ArchiveFile.read(&fileContent[0], fileContent.size());

            file.write(&fileContent[0], fileContent.size());

            file.clear();
            file.close();
        }

    }

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

//    for (auto fileHeader : m_HeaderCollection)
//    {
//        std::cout << std::endl;
//        std::cout << "File name: " << fileHeader.GetFileName() << std::endl;
//        std::cout << "File type: " << fileHeader.GetFileType() << std::endl;
//        std::cout << std::setbase(8);
//        std::cout << "File permissions: " << fileHeader.GetFilePermissions() << std::endl;
//        std::cout << std::setbase(10);
//        std::cout << "File size: " << fileHeader.GetFileSize() << std::endl;
//        std::cout << "File start pos: " << fileHeader.GetFileStartPosition() << std::endl;
//        std::cout << "File end pos: " << fileHeader.GetFileEndPosition() << std::endl;
//    }

//    std::cout << "######################################### All " << m_HeaderCollection.size() << " headers was read ###################################################" << std::endl;

}

}


