/*
 * ArchiveWriter.cpp
 *
 *  Created on: Nov 1, 2014
 *      Author: Oleksii Ozerov
 */


#include "ArchiveWriter.hpp"

#include "Header/Header.hpp"

#include <iostream>

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

void ArchiveWriter::WriteFileContent(const std::string& fileName)
{
    m_TempInputFile.open(fileName, std::ifstream::in);

    if (m_TempInputFile.is_open())
    {

        while (std::getline(m_TempInputFile, m_FileLine))
        {
            m_FileContent += m_FileLine;
        }

        if (!m_FileContent.empty())
        {
            m_ArchiveFile << m_FileContent;


            std::string fileBlockEnd(332, '\0');
            m_ArchiveFile << fileBlockEnd;

//            //todo
//            for (int i = 0; i < 332; ++i)
//            {
//                m_ArchiveFile.write() << '\0';
//            }

            m_FileContent.clear();
        }

        m_TempInputFile.close();
    }
}

void ArchiveWriter::WriteArchive()
{
    for (auto fileIterator = m_FileCollection.begin();
            fileIterator != m_FileCollection.end();
            ++fileIterator)
    {
        Header header(*fileIterator);

        header.WriteToFile(m_ArchiveFile);

        if (fileIterator->GetFileType() == boost::filesystem::regular_file)
        {
            WriteFileContent(fileIterator->GetFileName());
        }
    }

    WriteEndOfArchiveMarker();
}

void ArchiveWriter::WriteEndOfArchiveMarker()
{
    std::string endOfFileMarker(EndOfFileMarkerBytesNuber,'\0');

    m_ArchiveFile << endOfFileMarker;
}
}
