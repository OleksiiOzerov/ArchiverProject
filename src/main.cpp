//============================================================================
// Name        : ArchiverProject.cpp
// Author      : OleksiiOzerov
// Version     :
// Copyright   : All rights reserved.
// Description : Hello World in C++, Ansi-style
//============================================================================


#include "MainApp/MainApp.hpp"

#include <iostream>

int main(int argc, char* argv[])
{

    Archiver::MainApp::CreateApp(argc, argv);

    std::cout << "Program close" << std::endl;
    return 0;
}
