/*
 * MainApp.hpp
 *
 *  Created on: Oct 26, 2014
 *      Author: Oleksii Ozerov
 */

#ifndef MAINAPP_HPP_
#define MAINAPP_HPP_

namespace Archiver
{

class MainApp
{
public:

    static void CreateApp(int argc, char * argv[]);

    static void RunApp();

    static void CloseApp();

private:

    MainApp();
    MainApp(const MainApp &);
    const MainApp & operator=(const MainApp &);
};
}

#endif /* MAINAPP_HPP_ */
