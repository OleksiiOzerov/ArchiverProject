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
//enum FileManagerExceptionTypes {EMPTY_INPUT_ERROR, NO_EXISTING_FILE_ERROR};

class ArchiveReaderException : public std::exception
{
public:
    ArchiveReaderException(){}//(ArchiveReaderException errorType) : m_ErrorType(errorType) {}

    virtual const char* what() const throw()
    {
//        switch(m_ErrorType)
//        {
//            case EMPTY_INPUT_ERROR:
//                return "There is no file on input.";
//            case NO_EXISTING_FILE_ERROR:
//                return "There is no existing file on input.";
//            default:
//                return "Unhandled error";
//        }

        return "Archive do not exist";
    }

//private:
//    FileManagerExceptionTypes m_ErrorType;
};
}

#endif /* ARCHIVEREADEREXCEPTION_HPP_ */

