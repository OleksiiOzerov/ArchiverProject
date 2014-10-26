/*
 * CommandLineParser.hpp
 *
 *  Created on: Oct 25, 2014
 *      Author: Oleksii Ozerov
 */

#ifndef COMMANDLINEARGUMENTSPARSER_HPP_
#define COMMANDLINEARGUMENTSPARSER_HPP_

#include <string>
#include <vector>
#include <exception>


namespace Archiver
{
class CommandLineParser
{
public:

    class CommandLineException : public std::exception
    {
    public:
        virtual const char* what() const throw()
        {
            return "There is no input files to archive.";
        }
    };

    CommandLineParser(int argc, char * argv[]);

    const std::vector<std::string>& GetAllFileNames() const
    {
        return m_allFilesNames;
    }

private:

    std::string                 m_applicationName;

    std::vector<std::string>    m_allFilesNames;

};
}


#endif /* COMMANDLINEARGUMENTSPARSER_HPP_ */
