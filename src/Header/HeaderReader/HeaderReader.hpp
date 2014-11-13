/*
 * HeaderReader.hpp
 *
 *  Created on: Nov 6, 2014
 *      Author: Oleksii Ozerov
 */

#ifndef HEADERREADER_HPP_
#define HEADERREADER_HPP_

#include "../Header.hpp"

#include <string>

namespace Archiver
{

class HeaderReader
{
public:

    HeaderReader();

    bool ReadHeader(const std::string& headerString);

    Header GetHeader() const
    {
        return m_CurrentHeader;
    }

    size_t GetNextHeaderPosition() const
    {
        return m_NextHeaderPos;
    }

private:

    void CheckChksum(const std::string& headerString);

    void GetFileName(const std::string& headerString);

    boost::filesystem::file_type ConvertFileType(const std::string& fileType);

    void GetFileType(const std::string& headerString);

    void GetFilePermissions(const std::string& headerString);

    void GetFileSize(const std::string& headerString);

    void GetFileModificationTime(const std::string& headerString);

    void SetHeaderAndFilePositions();

    static const int BlockSize = 512;

    Header m_CurrentHeader;

    size_t m_NextHeaderPos;
};

}



#endif /* HEADERREADER_HPP_ */
