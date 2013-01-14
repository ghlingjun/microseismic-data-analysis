#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

//namespace Ui {
//class MainWindow;
//}
#define WIDTH 800
#define HEIGHT 600

class QLabel;
class QMenu;
class QAction;
class QScrollArea;

class CoordWidget;
class CoordSysWidget;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();

private slots:
    void about();

private:
//    Helper helper;
    void createMenus();
    void createActions();

    QWidget *centralWidget;
    QScrollArea *coordInputArea;
    QScrollArea *coordSysArea;
//    GLWidget *glWidget;
    QWidget *coordWidget;
    QWidget *coordSysWidget;

    QMenu *dataMenu;
    QMenu *modelMenu;
    QMenu *seismicSourceMenu;
    QMenu *helpMenu;
    QAction *fileFormatAct;
    QAction *mergeAct;
    QAction *signalAnalysisAct;
    QAction *exitAct;
    QAction *dividToGridAct;
    QAction *travelTimeCalcAct;
    QAction *aboutAct;
};

#endif // MAINWINDOW_H
