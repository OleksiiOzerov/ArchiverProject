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
    m_ApplicationName = argv[0];

    if (argc > 1)
    {
        m_InputFileNames.reserve(argc - 1);

        for (int i = 1; i < argc; ++i)
        {
            m_InputFileNames.push_back(argv[i]);
        }
    }
    else
    {
        throw CommandLineException();
    }
}
}
