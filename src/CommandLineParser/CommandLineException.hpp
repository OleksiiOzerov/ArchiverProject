/*
 * CommandLineException.hpp
 *
 *  Created on: Oct 27, 2014
 *      Author: ozerov
 */

#ifndef COMMANDLINEEXCEPTION_HPP_
#define COMMANDLINEEXCEPTION_HPP_

#include <exception>

namespace Archiver
{
class CommandLineException : public std::exception
{
public:
    virtual const char* what() const throw()
    {
        return "There is no input files in console.";
    }
};
}
#endif /* COMMANDLINEEXCEPTION_HPP_ */
