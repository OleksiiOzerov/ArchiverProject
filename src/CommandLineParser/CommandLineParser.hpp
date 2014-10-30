/*
 * CommandLineParser.hpp
 *
 *  Created on: Oct 25, 2014
 *      Author: Oleksii Ozerov
 */

#ifndef COMMANDLINEARGUMENTSPARSER_HPP_
#define COMMANDLINEARGUMENTSPARSER_HPP_

#include "CommandLineException.hpp"

#include <string>
#include <vector>

namespace Archiver
{
class CommandLineParser
{
public:

    CommandLineParser(int argc, char * argv[]);

    const std::vector<std::string>& GetAllFileNames() const
    {
        return m_InputFileNames;
    }

    const std::vector<std::string>& GetArchiveName() const
    {
        return m_InputFileNames;
    }

private:

    std::string                 m_ApplicationName;

    std::string                 m_ArchiveName;

    std::vector<std::string>    m_InputFileNames;

};
}


#endif /* COMMANDLINEARGUMENTSPARSER_HPP_ */
