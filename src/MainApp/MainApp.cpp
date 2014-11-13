/*
 * MainApp.cpp
 *
 *  Created on: Oct 26, 2014
 *      Author: Oleksii Ozerov
 */

#include "MainApp.hpp"

#include "../CommandLineParser/CommandLineParser.hpp"
#include "../FileManager/FileManager.hpp"
#include "../FileManager/FileProperties/FileProperties.hpp"
#include "../ArchiveWriter/ArchiveWriter.hpp"
#include "../ArchiveReader/ArchiveReader.hpp"


#include <iostream>

namespace Archiver
{

void MainApp::CreateApp(int argc, char * argv[])
{
    try
    {
        CommandLineParser commandLineParser(argc, argv);

        auto archiveName = commandLineParser.GetArchiveName();

        auto fileNames = commandLineParser.GetAllFileNames();

        if (!fileNames.empty())
        {
            FileManager fileManager(fileNames);

            std::vector<FileProperties> filesToArchive = std::move(fileManager.GetAllFilesRecursively());

            ArchiveWriter archiveWriter(archiveName, filesToArchive);

            archiveWriter.WriteArchive();
        }
        else
        {
            ArchiveReader archiveReader(archiveName);

            archiveReader.ReadAllHeaders();
        }
    }
    catch(const CommandLineException& commandLineException)
    {
        std::cout << "Exception in CommandLineParser was thrown:" << std::endl;
        std::cout << commandLineException.what() << std::endl;
    }
    catch(const FileManagerException& fileManagerException)
    {
        std::cout << "Exception in FileManager was thrown:" << std::endl;
        std::cout << fileManagerException.what() << std::endl;
    }
    catch(const ArchiveReaderException& archiveReaderException)
    {
        std::cout << "Exception in ArchiveReader was thrown:" << std::endl;
        std::cout << archiveReaderException.what() << std::endl;
    }
}

}
