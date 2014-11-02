/*
 * Header.cpp
 *
 *  Created on: Nov 2, 2014
 *      Author: Oleksii Ozerov
 */

#include "Header.hpp"

#include <iomanip>
#include <algorithm>

namespace Archiver
{
Header::Header(const FileProperties& fileProperties) :
                                 name(100, '\0'),
                                 mode(8, '\0'), //Currently not using
                                 //uid(8, '\0'),
                                 //gid(8, '\0'),
                                 uid({'0','0','1','7','5','0',' ','\0'}), //todo this is temporary solution
                                 gid({'0','0','1','7','5','0',' ','\0'}), //todo this is temporary solution
                                 size(12, '\0'),
                                 mtime(12, '\0'),
                                 chksum(8, ' '),
                                 typeflag(1, '\0'),
                                 linkname(100, '\0'),
                                 magic({'u','s','t','a','r','\0'}),
                                 version(2, '\0'),
                                 uname(32, '\0'),
                                 gname(32, '\0'),
                                 devmajor(8, '\0'),
                                 devminor(8, '\0'),
                                 prefix(131, '\0'),
                                 atime(12, '\0'),
                                 ctime(12, '\0'),
                                 m_FileProperties(fileProperties)
{
    const std::string& fileName = fileProperties.GetFileName();
    std::copy(fileName.begin(), fileName.end(), name.begin());

//    SetMode(fileProperties.GetFilePermissions());

    SetTypeFlag(fileProperties.GetFileType());

//    std::cout << mode << mode.size() << std::endl;
    std::cout << magic << magic.size() << std::endl;
}

//void Header::SetMode(boost::filesystem::perms filePermissions)
//{
//    mode.replace(0, 3, 3, '0');
//    mode.replace(3, 3, std::to_string(filePermissions));
//    mode[6] = ' ';
//}

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

void Header::WriteToFile(std::ofstream& archiveFile)
{
    archiveFile << name;

    //todo search for better solution
    archiveFile << std::setbase(8);
    archiveFile << "000";
    archiveFile << m_FileProperties.GetFilePermissions();
    archiveFile << ' ';
    archiveFile << '\0';
    archiveFile << std::setbase(10);

    archiveFile << uid;
    archiveFile << gid;

    //todo search for better solution, not work properly
    archiveFile << std::setbase(8);
    //archiveFile << size;
    archiveFile << m_FileProperties.GetFileSize();
    archiveFile << ' ';
    archiveFile << std::setbase(10);

    //todo search for better solution, not work properly
    archiveFile << std::setbase(8);
    archiveFile << m_FileProperties.GetileModificationTime();
    archiveFile << ' ';
    //archiveFile << mtime;
    archiveFile << std::setbase(10);

    archiveFile << chksum;
    archiveFile << typeflag;
    archiveFile << linkname;
    archiveFile << magic;
    archiveFile << version;
    archiveFile << uname;
    archiveFile << gname;
    archiveFile << devmajor;
    archiveFile << devminor;
    archiveFile << prefix;
    archiveFile << atime;
    archiveFile << ctime;
}

}


