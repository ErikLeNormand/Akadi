/**
  * \file main.c
  * \brief Minecraft painting generator
  * \author Erik Le Normand
  * \version 1.0
  * \date 29/07/2014
  *
  * This program is a tool to create and edit the Minecraft image where are all paintings.
  * These tables are decorative objects that can be seen in game.
  **/

#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
