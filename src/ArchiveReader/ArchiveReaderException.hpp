/*
 * ArchiveReaderException.hpp
 *
 *  Created on: Nov 6, 2014
 *      Author: Oleksii Ozerov
 */


#ifndef ARCHIVEREADEREXCEPTION_HPP_
#define ARCHIVEREADEREXCEPTION_HPP_

#include <exception>

namespace Archiver
{
enum ArchiveReaderExceptionTypes {EMPTY_ARCHIVE_NAME, FILE_OPEN_ERROR};

class ArchiveReaderException : public std::exception
{
public:
    ArchiveReaderException(ArchiveReaderExceptionTypes errorType) : m_ErrorType(errorType) {}

    virtual const char* what() const throw()
    {
        switch(m_ErrorType)
        {
            case EMPTY_ARCHIVE_NAME:
                return "Empty archive name.";
            case FILE_OPEN_ERROR:
                return "Archive do not exist or couldn't be open.";
            default:
                return "Unhandled error";
        }
    }

private:
    ArchiveReaderExceptionTypes m_ErrorType;
};
}

#endif /* ARCHIVEREADEREXCEPTION_HPP_ */

