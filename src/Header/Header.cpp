/*
 * Header.cpp
 *
 *  Created on: Nov 11, 2014
 *      Author: ozerov
 */


#include "Header.hpp"

namespace Archiver
{

Header::Header() : FileProperties(std::string()),
                m_FileStartPos(0),
                m_FileEndPos(0)
{
    //FileProperties(std::string());
}

Header::Header(std::string fileName) : FileProperties(fileName),
                                    m_FileStartPos(0),
                                    m_FileEndPos(0)
{
    //FileProperties(fileName);
}

}
