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
class QDialogButtonBox;

class CoordWidget;
class CoordSysWidget;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();

public slots:
    void accept();

private slots:
    void about();
    void drawCoordSys();

private:
//    Helper helper;
    void createMenus();
    void createActions();
    void createButtonBox();

    QWidget *centralWidget;
    QScrollArea *coordInputArea;
    QScrollArea *coordSysArea;
//    GLWidget *glWidget;
    CoordWidget *coordWidget;
    CoordSysWidget *coordSysWidget;

    QMenu *dataMenu;
    QMenu *modelMenu;
    QMenu *seismicSourceMenu;
    QMenu *helpMenu;
    QAction *fileFormatAct;
    QAction *mergeAct;
    QAction *signalAnalysisAct;
    QAction *exitAct;
    QAction *drawCoordSysAct;
    QAction *travelTimeCalcAct;
    QAction *aboutAct;

    QDialogButtonBox *buttonBox;
};

#endif // MAINWINDOW_H
