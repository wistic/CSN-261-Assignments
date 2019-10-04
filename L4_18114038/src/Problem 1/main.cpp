/**
* @file main.cpp
* @brief This Cpp file is a program used to start the GUI application.
*
* @author Prathamesh Katkar
*
* @date 04/09/2019
*/


#include "mainwindow.h"
#include <QApplication>
/**
* This method main() initialises the QApplication and starts the event loop.
* @param int argc, char const *argv[]
* @date 04/09/2019
*/
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
