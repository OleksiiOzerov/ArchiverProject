/*
 * Header.hpp
 *
 *  Created on: Nov 11, 2014
 *      Author: ozerov
 */

#ifndef HEADER_HPP_
#define HEADER_HPP_

#include "../FileManager/FileProperties/FileProperties.hpp"

namespace Archiver
{

class Header : public FileProperties
{
public:

    Header();

    Header(std::string fileName);

    void SetFileStartPosition(size_t fileStartPos)
    {
        m_FileStartPos = fileStartPos;
    }

    size_t GetFileStartPosition() const
    {
        return m_FileStartPos;
    }

    void SetFileEndPosition(size_t fileEndPos)
    {
        m_FileEndPos = fileEndPos;
    }

    size_t GetFileEndPosition() const
    {
        return m_FileEndPos;
    }

private:

    size_t m_FileStartPos;

    size_t m_FileEndPos;
};



}




#endif /* HEADER_HPP_ */
