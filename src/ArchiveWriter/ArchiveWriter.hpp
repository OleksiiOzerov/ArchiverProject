/*
 * ArchiveWriter.hpp
 *
 *  Created on: Nov 1, 2014
 *      Author: Oleksii Ozerov
 */

#ifndef ARCHIVEWRITER_HPP_
#define ARCHIVEWRITER_HPP_

#include "../FileManager/FileProperties/FileProperties.hpp"

#include <fstream>
#include <vector>

namespace Archiver
{
class ArchiveWriter
{
public:

    ArchiveWriter(std::string archiveName,
            const std::vector<FileProperties>& fileCollection);

    void WriteArchive();

    ~ArchiveWriter();

private:

    static const int EndOfFileMarkerBytesNuber = 512;

    void WriteFileContent(const std::string& fileName, uintmax_t fileSize);

    void WriteEndOfArchiveMarker();

    std::ofstream m_ArchiveFile;

    const std::vector<FileProperties>& m_FileCollection;

    std::ifstream m_TempInputFile;

    std::string m_FileContent;

    std::string m_FileLine;
};

}



#endif /* ARCHIVEWRITER_HPP_ */
