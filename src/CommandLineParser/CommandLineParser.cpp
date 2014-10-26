/*
 * CommandLineParser.cpp
 *
 *  Created on: Oct 25, 2014
 *      Author: Oleksii Ozerov
 */


#include "CommandLineParser.hpp"
namespace Archiver
{
CommandLineParser::CommandLineParser(int argc, char * argv[])
{
    m_applicationName = argv[0];

    if (argc - 1 > 0)
    {
        m_allFilesNames.reserve(argc - 1);

        for (int i = 1; i < argc; ++i)
        {
            m_allFilesNames.push_back(argv[i]);
        }
    }
    else
    {
        throw CommandLineException();
    }
}
}
