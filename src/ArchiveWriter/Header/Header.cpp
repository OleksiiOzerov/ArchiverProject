/*
 * Header.cpp
 *
 *  Created on: Nov 2, 2014
 *      Author: Oleksii Ozerov
 */

#include "Header.hpp"

#include <iomanip>
#include <algorithm>
#include <sstream>

namespace Archiver
{
Header::Header(const FileProperties& fileProperties) :
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
    const std::string& fileName = fileProperties.GetFileName();
    std::copy(fileName.begin(), fileName.end(), name.begin());

    SetMode(fileProperties.GetFilePermissions());

    SetSize(fileProperties.GetFileSize());

    SetTypeFlag(fileProperties.GetFileType());

    SetMtime(fileProperties.GetileModificationTime());

    uname.replace(0, 6, "ozerov");
    gname.replace(0, 6, "ozerov");
}

void Header::SetMode(boost::filesystem::perms filePermissions)
{
    std::ostringstream filePermissionString;
    filePermissionString << std::setbase(8);
    filePermissionString << std::setw(7) << std::setfill('0');
    filePermissionString << filePermissions;

    mode.replace(0, 7, filePermissionString.str());
}

void Header::SetSize(uintmax_t fileSize)
{
    std::ostringstream fileSizeString;
    fileSizeString << std::setbase(8);
    fileSizeString << std::setw(11) << std::setfill('0');
    fileSizeString << fileSize;

    size.replace(0, 11, fileSizeString.str());
}

void Header::SetMtime(std::time_t modificationTime)
{
    std::ostringstream fileSizeString;
    fileSizeString << std::setbase(8);
    fileSizeString << std::setw(11) << std::setfill('0');
    fileSizeString << modificationTime;

    mtime.replace(0, 11, fileSizeString.str());
}

void Header::SetTypeFlag(boost::filesystem::file_type fileType)
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

void Header::WriteChksum(std::string& archiveHeader)
{
    size_t chksumValue = 0;
    for (auto byte : archiveHeader)
    {
        chksumValue += byte;
    }

    std::ostringstream fileSizeString;
    fileSizeString << std::setbase(8);
    fileSizeString << std::setw(6) << std::setfill('0');
    fileSizeString << chksumValue;
    archiveHeader.replace(148, 6, fileSizeString.str());
    archiveHeader[154] = '\0';
}

void Header::WriteToFile(std::ofstream& archiveFile)
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


