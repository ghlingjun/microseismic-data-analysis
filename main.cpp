#include "mainwindow.h"
#include <QTranslator>

/*
author: Ethan
date: 2013-1-9
*/
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // 加载国际化文件
    QTranslator translator;
    translator.load("language.qm");
    app.installTranslator(&translator);

    MainWindow win;
    win.show();

    return app.exec();
}
