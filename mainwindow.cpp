#include <QtGui>
#include <QtOpenGL>

#include "coordwidget.h"
#include "coordsyswidget.h"
#include "mainwindow.h"

MainWindow::MainWindow()
{
    centralWidget = new QWidget;
    setCentralWidget(centralWidget);

    GLfloat points[] = {
        1.0f, 3.0f, 2.0f,
        2.0f, 3.0f, 2.0f,
        3.0f, 3.0f, 2.0f
    };
    coordWidget = new CoordWidget;
    coordSysWidget = new CoordSysWidget(0, points, 9);

    coordInputArea = new QScrollArea;
    coordInputArea->setWidget(coordWidget);
    coordInputArea->setWidgetResizable(true);
    coordInputArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    coordInputArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    coordInputArea->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    coordInputArea->setMinimumSize(50, 50);

    coordSysArea = new QScrollArea;
    coordSysArea->setWidget(coordSysWidget);
    coordSysArea->setWidgetResizable(true);
    coordSysArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    coordSysArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    coordSysArea->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    coordSysArea->setMinimumSize(50, 50);

    createActions();
    createMenus();

    QGridLayout *centralLayout = new QGridLayout;
    centralLayout->addWidget(coordInputArea, 0, 0, 1, 1);
    centralLayout->addWidget(coordSysArea, 0, 1, 1, 2);
//    centralLayout->addWidget(glWidgetArea, 0, 2);
    centralWidget->setLayout(centralLayout);

    setWindowTitle(tr("Microseismic Data Analysis"));
    resize(WIDTH, HEIGHT);
}

void MainWindow::about()
{
    QMessageBox::about(this, tr("About Microseismic"),
                       tr("The <b>Microseismic</b> ... "
                          "The development environment is QT, Used C++ and OpenGL."));
}

void MainWindow::createActions()
{
    fileFormatAct = new QAction(tr("Format"), this);
    fileFormatAct->setShortcut(tr("Ctrl+F"));

    mergeAct = new QAction(tr("Merger"), this);
    mergeAct->setShortcut(tr("Ctrl+M"));

    signalAnalysisAct = new QAction(tr("Signal Analysis"), this);
    signalAnalysisAct->setShortcut(tr("Ctrl+I"));

    exitAct = new QAction(tr("E&xit"), this);
    exitAct->setShortcuts(QKeySequence::Quit);
    connect(exitAct, SIGNAL(triggered()), this, SLOT(close()));

    dividToGridAct = new QAction(tr("Divide To Grid"), this);
    dividToGridAct->setShortcut(tr("Ctrl+D"));

    travelTimeCalcAct = new QAction(tr("Travel Time"), this);
    travelTimeCalcAct->setShortcut(tr("Ctrl+T"));

    aboutAct = new QAction(tr("&About"), this);
    connect(aboutAct, SIGNAL(triggered()), this, SLOT(about()));

}

void MainWindow::createMenus()
{
    dataMenu = menuBar()->addMenu(tr("Data Pre Process"));
    dataMenu->addAction(fileFormatAct);
    dataMenu->addAction(mergeAct);
    dataMenu->addAction(signalAnalysisAct);
    dataMenu->addSeparator();
    dataMenu->addAction(exitAct);

    modelMenu = menuBar()->addMenu(tr("Model Build"));
    modelMenu->addAction(dividToGridAct);
    modelMenu->addAction(travelTimeCalcAct);

    seismicSourceMenu = menuBar()->addMenu(tr("Microseismic Point"));

    helpMenu = menuBar()->addMenu(tr("&Help"));
    helpMenu->addAction(aboutAct);
}
