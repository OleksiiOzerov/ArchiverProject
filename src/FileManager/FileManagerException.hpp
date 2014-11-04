/*
 * FileManagerException.hpp
 *
 *  Created on: Oct 27, 2014
 *      Author: ozerov
 */

#ifndef FILEMANAGEREXCEPTION_HPP_
#define FILEMANAGEREXCEPTION_HPP_

#include <exception>

namespace Archiver
{
enum FileManagerExceptionTypes {EMPTY_INPUT_ERROR, NO_EXISTING_FILE_ERROR};

class FileManagerException : public std::exception
{
public:
    FileManagerException(FileManagerExceptionTypes errorType) : m_ErrorType(errorType) {}

    virtual const char* what() const throw()
    {
        switch(m_ErrorType)
        {
            case EMPTY_INPUT_ERROR:
                return "There is no file on input.";
            case NO_EXISTING_FILE_ERROR:
                return "There is no existing file on input.";
            default:
                return "Unhandled error";
        }
    }

private:
    FileManagerExceptionTypes m_ErrorType;
};
}

#endif /* FILEMANAGEREXCEPTION_HPP_ */
