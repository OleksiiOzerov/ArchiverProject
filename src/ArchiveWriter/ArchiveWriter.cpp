/*
 * ArchiveWriter.cpp
 *
 *  Created on: Nov 1, 2014
 *      Author: Oleksii Ozerov
 */


#include "ArchiveWriter.hpp"

#include "../Header/HeaderWriter/HeaderWriter.hpp"

#include <iostream>
#include <sstream>
namespace Archiver
{

ArchiveWriter::ArchiveWriter(std::string archiveName,
                             const std::vector<FileProperties>& fileCollection) :
                    m_ArchiveFile(archiveName, std::ios::out | std::ios::trunc | std::ios::binary),
                    m_FileCollection(fileCollection)
{
}

ArchiveWriter::~ArchiveWriter()
{
    m_ArchiveFile.close();
}

void ArchiveWriter::WriteFileContent(const std::string& fileName, uintmax_t fileSize)
{
    if (fileSize != 0)
    {
        m_TempInputFile.open(fileName, std::ifstream::in | std::ifstream::binary);

        if (m_TempInputFile.is_open())
        {
            //another way to read a file need to check efficiency
            //int additionalByteNumber = 512 - fileSize % 512;
            //m_FileContent.reserve(fileSize + additionalByteNumber);
            //m_FileContent.assign((std::istreambuf_iterator<char>(m_TempInputFile)),
            //std::istreambuf_iterator<char>());

            std::stringstream stringStream;
            stringStream << m_TempInputFile.rdbuf();//read the file
            m_FileContent = std::move(stringStream.str());

            if (!m_FileContent.empty())
            {
                int lastBlockSize = m_FileContent.size() % 512;

                m_FileContent.append(512 - lastBlockSize, '\0');

                m_ArchiveFile << m_FileContent;

                m_FileContent.clear();
            }
            m_TempInputFile.clear();
            m_TempInputFile.close();
        }
    }
}

void ArchiveWriter::WriteArchive()
{
    for (auto fileIterator = m_FileCollection.begin();
            fileIterator != m_FileCollection.end();
            ++fileIterator)
    {
        HeaderWriter headerWriter(*fileIterator);

        headerWriter.WriteToFile(m_ArchiveFile);

        if (fileIterator->GetFileType() == boost::filesystem::regular_file)
        {
            WriteFileContent(fileIterator->GetFileName(), fileIterator->GetFileSize());
        }
    }

    WriteEndOfArchiveMarker();
}

void ArchiveWriter::WriteEndOfArchiveMarker()
{
    std::string endOfFileMarker(EndOfFileMarkerBytesNuber * 10, '\0');

    m_ArchiveFile << endOfFileMarker;
}
}
