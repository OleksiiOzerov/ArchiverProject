/*
 * HeaderWriter.cpp
 *
 *  Created on: Nov 2, 2014
 *      Author: Oleksii Ozerov
 */

#include "HeaderWriter.hpp"

#include <iomanip>
#include <algorithm>


namespace Archiver
{
HeaderWriter::HeaderWriter(const FileProperties& fileProperties) :
                                 name(100, '\0'),
                                 mode(8, '\0'), //Currently not using
                                 //uid(8, '\0'),
                                 //gid(8, '\0'),
                                 uid({'0','0','0','1','7','5','0','\0'}), //todo this is temporary solution
                                 gid({'0','0','0','1','7','5','0','\0'}), //todo this is temporary solution
                                 size(12, '\0'),
                                 mtime(12, '\0'),
                                 chksum(8, ' '),
                                 typeflag(1, '\0'),
                                 linkname(100, '\0'),
                                 magic({'u','s','t','a','r',' '}),
                                 //version(2, '\0'),
                                 version({' ', '\0'}),
                                 uname(32, '\0'),
                                 gname(32, '\0'),
                                 devmajor(8, '\0'),
                                 devminor(8, '\0'),
                                 prefix(131, '\0'),
                                 atime(12, '\0'),
                                 ctime(12, '\0'),
                                 end(12, '\0')
{
    std::string fileName = fileProperties.GetFileName();

    if (fileProperties.GetFileType() == boost::filesystem::directory_file)
        fileName.append(1, '/');

    std::copy(fileName.begin(), fileName.end(), name.begin());

    SetMode(fileProperties.GetFilePermissions());

    SetSize(fileProperties.GetFileSize());

    SetTypeFlag(fileProperties.GetFileType());

    SetMtime(fileProperties.GetFileModificationTime());

    uname.replace(0, 6, "ozerov");
    gname.replace(0, 6, "ozerov");
}

void HeaderWriter::SetMode(boost::filesystem::perms filePermissions)
{
    m_StringStream << std::setbase(8);
    m_StringStream << std::setw(7) << std::setfill('0');
    m_StringStream << filePermissions;

    std::string modeString = m_StringStream.str();
    modeString.resize(7);

    mode.replace(0, 7, modeString);

    m_StringStream.seekp(std::ios::beg);
}

void HeaderWriter::SetSize(uintmax_t fileSize)
{
    m_StringStream << std::setbase(8);
    m_StringStream << std::setw(11) << std::setfill('0');
    m_StringStream << fileSize;

    std::string sizeString = m_StringStream.str();
    sizeString.resize(11);

    size.replace(0, 11, sizeString);

    m_StringStream.seekp(std::ios::beg);
}

void HeaderWriter::SetMtime(std::time_t modificationTime)
{
    m_StringStream << std::setbase(8);
    m_StringStream << std::setw(11) << std::setfill('0');
    m_StringStream << modificationTime;

    std::string timeString = m_StringStream.str();
    timeString.resize(11);

    mtime.replace(0, 11, timeString);

    m_StringStream.seekp(std::ios::beg);
}

void HeaderWriter::SetTypeFlag(boost::filesystem::file_type fileType)
{
    switch(fileType)
    {
    case boost::filesystem::regular_file:
        typeflag[0] = '0';
        break;
//    case boost::filesystem::regular_file:
//        typeflag[0] = '1';
//        break;
    case boost::filesystem::symlink_file:
        typeflag[0] = '2';
        break;
    case boost::filesystem::character_file:
        typeflag[0] = '3';
        break;
    case boost::filesystem::block_file:
        typeflag[0] = '4';
        break;
    case boost::filesystem::directory_file:
        typeflag[0] = '5';
        break;
    case boost::filesystem::fifo_file:
        typeflag[0] = '6';
        break;
//    case boost::filesystem::regular_file:
//        typeflag[0] = '7';
//        break;
    default:
        typeflag[0] = '\0';
    }
}

void HeaderWriter::WriteChksum(std::string& archiveHeader)
{
    size_t chksumValue = 0;
    for (auto byte : archiveHeader)
    {
        chksumValue += byte;
    }

    m_StringStream << std::setbase(8);
    m_StringStream << std::setw(6) << std::setfill('0');
    m_StringStream << chksumValue;

    std::string chksumString = m_StringStream.str();
    chksumString.resize(6);

    archiveHeader.replace(148, 6, chksumString);

    m_StringStream.seekp(std::ios::beg);
    archiveHeader[154] = '\0';
}

void HeaderWriter::WriteToFile(std::ofstream& archiveFile)
{
    std::string archiveHeader;
    archiveHeader.reserve(512);

    archiveHeader += name;
    archiveHeader += mode;
    archiveHeader += uid;
    archiveHeader += gid;
    archiveHeader += size;
    archiveHeader += mtime;
    archiveHeader += chksum;
    archiveHeader += typeflag;
    archiveHeader += linkname;
    archiveHeader += magic;
    archiveHeader += version;
    archiveHeader += uname;
    archiveHeader += gname;
    archiveHeader += devmajor;
    archiveHeader += devminor;
    archiveHeader += prefix;
    archiveHeader += atime;
    archiveHeader += ctime;
    archiveHeader += end;

    WriteChksum(archiveHeader);

    archiveFile << archiveHeader;
}

}
