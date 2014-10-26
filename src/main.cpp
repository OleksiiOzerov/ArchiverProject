//============================================================================
// Name        : ArchiverProject.cpp
// Author      : OleksiiOzerov
// Version     :
// Copyright   : All rights reserved.
// Description : Hello World in C++, Ansi-style
//============================================================================


#include "MainApp/MainApp.hpp"

int main(int argc, char* argv[])
{

//    boost::filesystem::path directoryPath("SampleDir");
//    if (boost::filesystem::exists(directoryPath))
//    {
//        if (boost::filesystem::is_directory(directoryPath))
//        {
//           std::cout << directoryPath << " is a directory containing:\n";
//
//           std::copy(boost::filesystem::directory_iterator(directoryPath),
//                     boost::filesystem::directory_iterator(),
//                     std::ostream_iterator<boost::filesystem::directory_entry>(std::cout, "\n"));
//        }
//    }


//    try
//    {
//        CommandLineParser commandLineParser(argc, argv);
//
//        auto fileNames = commandLineParser.GetAllFileNames();
//
////        std::copy(fileNames.begin(), fileNames.end(), std::ostream_iterator<std::string>(std::cout, " "));
////        std::cout << std::endl;
//
//        FileManager fileManager(fileNames);
//        fileManager.PrintAllFiles();
//    }
//    catch(CommandLineParser::CommandLineException & commandLineException)
//    {
//        std::cout << "Exception was thrown:" << std::endl;
//        std::cout << commandLineException.what() << std::endl;
//    }


    Archiver::MainApp::CreateApp(argc, argv);

    std::cout << "Program end" << std::endl;
    return 0;
}
