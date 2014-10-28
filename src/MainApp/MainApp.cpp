/*
 * MainApp.cpp
 *
 *  Created on: Oct 26, 2014
 *      Author: Oleksii Ozerov
 */

#include "MainApp.hpp"

#include "../CommandLineParser/CommandLineParser.hpp"
#include "../FileManager/FileManager.hpp"

#include <iostream>

namespace Archiver
{

void MainApp::CreateApp(int argc, char * argv[])
{
    try
    {
        CommandLineParser commandLineParser(argc, argv);

        auto fileNames = commandLineParser.GetAllFileNames();

        FileManager fileManager(fileNames);

        std::vector<std::string> filesToArchive(fileManager.GetAllFiles());

        std::copy(filesToArchive.begin(), filesToArchive.end(), std::ostream_iterator<std::string>(std::cout, "\n"));
        std::cout << std::endl;
    }
    catch(CommandLineException & commandLineException)
    {
        std::cout << "Exception in CommandLineParser was thrown:" << std::endl;
        std::cout << commandLineException.what() << std::endl;
    }
    catch(FileManagerException & fileManagerException)
    {
        std::cout << "Exception in FileManager was thrown:" << std::endl;
        std::cout << fileManagerException.what() << std::endl;
    }
}

}
