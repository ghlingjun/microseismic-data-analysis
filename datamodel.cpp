#include "datamodel.h"

#include <QtDebug>
#include <QtSql>

DataModel::DataModel(QWidget *parent) :
    QWidget(parent)
{
    dbconn = new DBConn();

    qDebug() << "DataModel constructor begin...\n";
    if(dbconn->createConnection())
    {
        qDebug() << "Connection success...\n";
        model = new QSqlTableModel;
    }
    else
    {
        qDebug() << "Connection failed...";
    }
}

DataModel * DataModel::instance = 0;

DataModel * DataModel::getInstance()
{
    {
        if(0 == instance)
        {
            instance = new DataModel();
        }
        return instance;
    }
}

void DataModel::initializeModel()
 {
     model->setTable("msdata");
//     model->setQuery("select * from msdata");
//     model->setEditStrategy(QSqlTableModel::OnManualSubmit);
     model->select();

     model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
     model->setHeaderData(1, Qt::Horizontal, QObject::tr("Name"));
     model->setHeaderData(2, Qt::Horizontal, QObject::tr("X"));
     model->setHeaderData(3, Qt::Horizontal, QObject::tr("Y"));
     model->setHeaderData(4, Qt::Horizontal, QObject::tr("Z"));
     model->setHeaderData(5, Qt::Horizontal, QObject::tr("Longitude"));
     model->setHeaderData(6, Qt::Horizontal, QObject::tr("Latitude"));
     model->setHeaderData(7, Qt::Horizontal, QObject::tr("Altitude"));
     model->setHeaderData(8, Qt::Horizontal, QObject::tr("Pressure"));
     model->setHeaderData(9, Qt::Horizontal, QObject::tr("Time"));
 }

QTableView * DataModel::createView(const QString &title)
 {
     view = new QTableView;
     view->setSizePolicy(QSizePolicy::Preferred,
                         QSizePolicy::Ignored);
     view->setModel(model);
//     view->setWindowTitle(title);
     return view;
 }

QTableView * DataModel::getTableView()
{
    return view;
}

QSqlTableModel * DataModel::getTableModel()
{
    return model;
}
