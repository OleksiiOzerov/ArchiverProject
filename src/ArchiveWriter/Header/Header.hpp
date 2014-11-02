/*
 * Header.hpp
 *
 *  Created on: Nov 2, 2014
 *      Author: Oleksii Ozerov
 */

#ifndef HEADER_HPP_
#define HEADER_HPP_

#include "../../FileManager/FileProperties/FileProperties.hpp"

#include <string>
#include <fstream>
namespace Archiver
{
struct Header
{
private:

    std::string name;       /*   0 */
    std::string mode;       /* 100 */
    std::string uid;        /* 108 */
    std::string gid;        /* 116 */
    std::string size;       /* 124 */
    std::string mtime;      /* 136 */
    std::string chksum;     /* 148 */
    std::string typeflag;   /* 156 */
    std::string linkname;   /* 157 */
    std::string magic;      /* 257 */
    std::string version;    /* 263 */
    std::string uname;      /* 265 */
    std::string gname;      /* 297 */
    std::string devmajor;   /* 329 */
    std::string devminor;   /* 337 */
    std::string prefix;     /* 345 */
    std::string atime;      /* 476 */
    std::string ctime;      /* 488 */
                            /* 500 */

    const FileProperties m_FileProperties;
public:

    Header(const FileProperties& fileProperties);

    void WriteToFile(std::ofstream& archiveFile);

private:

    void SetTypeFlag(boost::filesystem::file_type fileType);

//    void SetMode(boost::filesystem::perms filePermissions);
};
}

#endif /* HEADER_HPP_ */
