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
    m_TempInputFile.open(fileName, std::ifstream::in | std::ifstream::binary);

    if (m_TempInputFile.is_open())
    {

//        while (std::getline(m_TempInputFile, m_FileLine))
//        {
//
//            m_FileContent += m_FileLine;
//        }


        //Todo: do optimization with reserve on whole file size
        while (m_TempInputFile.good())
        {
            char byte = m_TempInputFile.get();

            if (m_TempInputFile.good())
            {
                m_FileContent.push_back(byte);
            }
        }


        if (!m_FileContent.empty())
        {
            int lastBlockSize = m_FileContent.size() % 512 ;

            m_FileContent.append(512 - lastBlockSize, '\0');

            m_ArchiveFile << m_FileContent;

            m_FileContent.clear();
        }
        m_TempInputFile.clear();
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
    std::string endOfFileMarker(EndOfFileMarkerBytesNuber * 18,'\0');

    m_ArchiveFile << endOfFileMarker;
}
}
