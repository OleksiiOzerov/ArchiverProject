/*
 * HeaderReaderException.hpp
 *
 *  Created on: Nov 13, 2014
 *      Author: ozerov
 */

#ifndef HEADERREADEREXCEPTION_HPP_
#define HEADERREADEREXCEPTION_HPP_

#include <exception>

namespace Archiver
{
enum HeaderReaderExceptionTypes {CHECKSUM_ERROR, HEADER_CORRUPTED, FILE_TYPE_UNKNOWN, END_OF_ARCHIVE};

class HeaderReaderException : public std::exception
{
public:
    HeaderReaderException(HeaderReaderExceptionTypes errorType) : m_ErrorType(errorType) {}

    virtual const char* what() const throw()
    {
        switch(m_ErrorType)
        {
            case CHECKSUM_ERROR:
                return "Checksum error.";

            case HEADER_CORRUPTED:
                return "Header corrupted.";

            case FILE_TYPE_UNKNOWN:
                return "File type unknown.";

            case END_OF_ARCHIVE:
                return "End of archive reached.";

            default:
                return "Unhandled error";
        }
    }

    HeaderReaderExceptionTypes GetErrorType()const
    {
        return m_ErrorType;
    }

private:
    HeaderReaderExceptionTypes m_ErrorType;
};
}

#endif /* HEADERREADEREXCEPTION_HPP_ */
