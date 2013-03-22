#ifndef DATAMODEL_H
#define DATAMODEL_H

#include <QWidget>
#include <QSqlTableModel>
#include <QTableView>

#include "dbconn.h"

class QTableWidget;

class DataModel : public QWidget
{
    Q_OBJECT
private:
    explicit DataModel(QWidget *parent = 0);

    QSqlTableModel *model;
    QTableView *view;
    static DataModel * instance;
    DBConn *dbconn;

public:
//    explicit DataModel(QWidget *parent = 0);

    static DataModel * getInstance();

    void initializeModel();
    QTableView *createView(const QString &title);

    QTableView *getTableView();
    QSqlTableModel *getTableModel();

signals:

public slots:

};

#endif // DATAMODEL_H
