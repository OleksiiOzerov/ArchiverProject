/*
 * HeaderReader.cpp
 *
 *  Created on: Nov 11, 2014
 *      Author: ozerov
 */

#include "HeaderReader.hpp"

#include "HeaderReaderException.hpp"

#include <numeric>

namespace Archiver
{

HeaderReader::HeaderReader() : m_CurrentHeader(), m_NextHeaderPos(0)
{
}

void HeaderReader::CheckChksum(const std::string& headerString)
{
//    std::cout << std::endl;

    auto checkSumReal = std::accumulate(headerString.begin(), headerString.end(), 0u);

    if (checkSumReal == 0u)
        throw HeaderReaderException(END_OF_ARCHIVE);

    std::string checkSumEstimatedString = headerString.substr(148, 8);

    size_t checkSumEstimated = 0;

    try
    {
        checkSumEstimated = std::stoi(checkSumEstimatedString, nullptr, 8);
    }
    catch(...)
    {
        throw HeaderReaderException(HEADER_CORRUPTED);
    }

//    std::cout << "checkSumEstimated = " << checkSumEstimated << std::endl;

    checkSumReal -= std::accumulate(checkSumEstimatedString.begin(), checkSumEstimatedString.end(), 0u);

    checkSumReal += 8 * int(' ');

//    std::cout << "checkSumReal = " << checkSumReal << std::endl;

    if (checkSumReal != checkSumEstimated)
        throw HeaderReaderException(CHECKSUM_ERROR);
}

void HeaderReader::GetFileName(const std::string& headerString)
{
//    std::cout << std::endl;

    std::string fileName = headerString.substr(0, 100);

    size_t nameEndPos = fileName.find('\0');

    fileName.erase(nameEndPos);

//    std::cout << "FileName = " << fileName << "  " << fileName.size() << std::endl;

    m_CurrentHeader.SetFileName(fileName);
}

boost::filesystem::file_type HeaderReader::ConvertFileType(const std::string& fileType)
{
    switch(fileType[0])
    {
    case '0':
        return boost::filesystem::regular_file;

//    case boost::filesystem::regular_file:
//        typeflag[0] = '1';
//        break;

    case '2':
        return boost::filesystem::symlink_file;

    case '3':
        return boost::filesystem::character_file;

    case '4':
        return boost::filesystem::block_file;

    case '5':
        return boost::filesystem::directory_file;

    case '6':
        return boost::filesystem::fifo_file;

//    case boost::filesystem::regular_file:
//        typeflag[0] = '7';
//        break;

    default:
        throw HeaderReaderException(FILE_TYPE_UNKNOWN);
    }
}

void HeaderReader::GetFileType(const std::string& headerString)
{
//    std::cout << std::endl;

    std::string fileTypeString = headerString.substr(156, 1);

//    std::cout << "fileTypeString = " << fileTypeString << std::endl;

    auto fyleType = ConvertFileType(fileTypeString);

    m_CurrentHeader.SetFileType(fyleType);

}

void HeaderReader::GetFilePermissions(const std::string& headerString)
{
//    std::cout << std::endl;

    std::string filePermissionString = headerString.substr(100, 8);

//    std::cout << "filePermissionString = " << filePermissionString << std::endl;

    boost::filesystem::perms filePermissions = boost::filesystem::perms_not_known;
    try
    {
        filePermissions = (boost::filesystem::perms)std::stoi(filePermissionString, nullptr, 8);
    }
    catch(...)
    {
        throw HeaderReaderException(HEADER_CORRUPTED);
    }
//    std::cout << "filePermissionString = " << filePermissions << std::endl;

    m_CurrentHeader.SetFilePermissions(filePermissions);
}

void HeaderReader::GetFileSize(const std::string& headerString)
{
//    std::cout << std::endl;

    std::string fileSizeString = headerString.substr(124, 11);

//    std::cout << "fileSizeString = " << fileSizeString << std::endl;

    uintmax_t fileSize = std::stoi(fileSizeString, nullptr, 8);

//    std::cout << "fileSize = " << fileSize << std::endl;

    m_CurrentHeader.SetFileSize(fileSize);
}

void HeaderReader::GetFileModificationTime(const std::string& headerString)
{
//    std::cout << std::endl;

    std::string fileModificationTimeString = headerString.substr(136, 11);

//    std::cout << "fileModificationTimeString = " << fileModificationTimeString << std::endl;

    std::time_t fileModificationTime = std::stoi(fileModificationTimeString, nullptr, 8);

//    std::cout << "fileModificationTime = " << fileModificationTime << std::endl;

    m_CurrentHeader.SetFileModificationTime(fileModificationTime);
}

void HeaderReader::SetHeaderAndFilePositions()
{
//    std::cout << std::endl;

    uintmax_t fileSize = m_CurrentHeader.GetFileSize();

    if (fileSize == uintmax_t(0))
    {
        m_CurrentHeader.SetFileStartPosition(0);
        m_CurrentHeader.SetFileEndPosition(0);
        m_NextHeaderPos = m_NextHeaderPos + BlockSize;
    }
    else
    {
        m_CurrentHeader.SetFileStartPosition(m_NextHeaderPos + BlockSize);
        m_CurrentHeader.SetFileEndPosition(m_NextHeaderPos + BlockSize + fileSize);
        m_NextHeaderPos = m_NextHeaderPos + fileSize + (BlockSize - fileSize % BlockSize) + BlockSize;
    }

//    std::cout << "start pos = " << m_CurrentHeader.GetFileStartPosition() << std::endl;
//    std::cout << "end pos = " << m_CurrentHeader.GetFileEndPosition() << std::endl;
//    std::cout << "m_NextHeaderPos = " << m_NextHeaderPos << std::endl;
}

bool HeaderReader::ReadHeader(const std::string& headerString)
{
    try
    {
//        std::cout << std::endl;
//        for (auto symbol : headerString)
//        {
//            std::cout << symbol;
//        }
//        std::cout << std::endl;

        CheckChksum(headerString);

        GetFileName(headerString);

        GetFileType(headerString);

        GetFilePermissions(headerString);

        GetFileSize(headerString);

        SetHeaderAndFilePositions();

    }
    catch(const HeaderReaderException& headerReaderException)
    {
        switch(headerReaderException.GetErrorType())
        {
//        case CHECKSUM_ERROR:
//            throw;
//            break;
//
//        case FILE_TYPE_UNKNOWN:
//            throw;
//            break;

        case END_OF_ARCHIVE:
            return false;
            break;

        default:
            throw;
        }
    }

    return true;
}

}

