#include <QtGui>
#include <QtOpenGL>

#include "coordsyswidget.h"
#include "mainwindow.h"

MainWindow::MainWindow()
{
    centralWidget = new QWidget;
    setCentralWidget(centralWidget);

//    glWidget = new GLWidget;
    coordWidget = new CoordSysWidget;

//    glWidgetArea = new QScrollArea;
//    glWidgetArea->setWidget(glWidget);
//    glWidgetArea->setWidgetResizable(true);
//    glWidgetArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
//    glWidgetArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
//    glWidgetArea->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
//    glWidgetArea->setMinimumSize(50, 50);

    coordSysArea = new QScrollArea;
    coordSysArea->setWidget(coordWidget);
    coordSysArea->setWidgetResizable(true);
    coordSysArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    coordSysArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    coordSysArea->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    coordSysArea->setMinimumSize(50, 50);

    createActions();
    createMenus();

    QGridLayout *centralLayout = new QGridLayout;
    centralLayout->addWidget(coordSysArea, 0, 1);
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
//    connect(mergeAct, SIGNAL(triggered()), this, SLOT(clearPixmap()));

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
