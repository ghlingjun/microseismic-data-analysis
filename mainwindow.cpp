#include <QtGui>
#include <QtOpenGL>

#include "coordwidget.h"
#include "coordsyswidget.h"
#include "mainwindow.h"

/**
  author: Ethan
  date: 2013-1-9
  */
MainWindow::MainWindow()
{
    centralWidget = new QWidget;
    setCentralWidget(centralWidget);

    coordWidget = new CoordWidget; // 坐标点输入控件
    createButtonBox();
    coordSysWidget = new CoordSysWidget; // 坐标系显示控件

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

    // 创建动作和菜单
    createActions();
    createMenus();

    // 布局控制
    QGridLayout *centralLayout = new QGridLayout;
    centralLayout->addWidget(coordInputArea, 0, 0, 1, 1);
    centralLayout->setColumnStretch(0, 200);
    centralLayout->setColumnStretch(1, 500);
    centralLayout->addWidget(coordSysArea, 0, 1, 1, 2);
    centralLayout->addWidget(buttonBox, 1, 0, 1, 1);
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

void MainWindow::createButtonBox()
{
    buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok
                                     | QDialogButtonBox::Cancel);

    connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
}

/**
  当确定时，把文本控件内的内容解析，得到要画出的坐标点，并在坐标系中绘出所有点
  */
void MainWindow::accept()
{
    GLfloat points[POINTSNUM][3];
    QString pointNames[POINTSNUM];
    int index = 0;
    QString coord = 0; // left string
    QStringList strlist; // one coordinate
    int pointsIndex = 0; // points array cursor
    QString text = 0;

    QTextEdit *textEdit = coordWidget->getTextEdit();
    text.append(textEdit->toPlainText());
    // cut from '{'
    QString coordStr = text.mid(text.indexOf('{') + 1).trimmed();
    index = coordStr.indexOf(';');
    // get coordinate and remove the ';'
    coord = coordStr.left(index + 1).left(index).trimmed();
    while(coord.compare("")!=1 && index!=-1) {
        // remove the coord
        coordStr = coordStr.mid(index + 1);
        strlist = coord.split(',');
        pointNames[pointsIndex] = strlist.at(0).trimmed();
        points[pointsIndex][0] = strlist.at(1).toFloat();
        points[pointsIndex][1] = strlist.at(2).toFloat();
        points[pointsIndex][2] = strlist.at(3).toFloat();
        pointsIndex++;
        index = coordStr.indexOf(';');
        coord = coordStr.left(index + 1).left(index).trimmed();
    }

    delete coordSysWidget;
    coordSysWidget = new CoordSysWidget(0, points, pointNames);
    coordSysArea->setWidget(coordSysWidget);
}
