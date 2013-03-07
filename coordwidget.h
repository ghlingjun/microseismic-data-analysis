#ifndef COORDWIDGET_H
#define COORDWIDGET_H

#include <QtOpenGL>
#include <QSqlTableModel>

#include "DataModel.h"

class QLineEdit;
class QProgressBar;
class QTabWidget;
class QTableWidget;
class QTextEdit;

class DataModel;

class CoordWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CoordWidget(QWidget *parent = 0);
    QTextEdit* getTextEdit();

signals:

public slots:

private slots:
    void advanceProgressBar();

private:
    void createTextWidget();
    void createProgressBar();
    void createTbl();

    void initializeModel(QSqlTableModel *model);
    QTableView *createView(const QString &title, QSqlTableModel *model);

    QPalette originalPalette;

    QTabWidget *textWidget;
//    QTableWidget *tableWidget;
    QTableView *tableView;
    QTextEdit *textEdit;

    QProgressBar *progressBar;
};

#endif // COORDWIDGET_H
