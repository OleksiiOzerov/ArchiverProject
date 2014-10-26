/*
 * MainApp.cpp
 *
 *  Created on: Oct 26, 2014
 *      Author: Oleksii Ozerov
 */


#include "MainApp.hpp"

namespace Archiver
{

void MainApp::CreateApp(int argc, char * argv[])
{
    try
    {
        CommandLineParser commandLineParser(argc, argv);

        auto fileNames = commandLineParser.GetAllFileNames();

//        std::copy(fileNames.begin(), fileNames.end(), std::ostream_iterator<std::string>(std::cout, " "));
//        std::cout << std::endl;

        FileManager fileManager(fileNames);
        fileManager.PrintAllFiles();
    }
    catch(CommandLineParser::CommandLineException & commandLineException)
    {
        std::cout << "Exception was thrown:" << std::endl;
        std::cout << commandLineException.what() << std::endl;
    }
}

}
