//============================================================================
// Name        : QtGui.cpp
// Author      : Thomas Kittel
// Version     :
// Copyright   : (c) Thomas Kittel
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <QtGui>

#include "MainWindow.h"

 int main(int argc, char *argv[])
 {
     QApplication app(argc, argv);
     MainWindow window;

     window.setWindowTitle(
         QApplication::translate("vmiids_control_center", "VmiIDS Control Center"));
     window.show();
     return app.exec();
 }
