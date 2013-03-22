#ifndef DBCONN_H
#define DBCONN_H

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QtDebug>

#include "readconfig.h"

/**
 * @author: Ethan
 * @date: 2013-3-20
 */
class DBConn
{
public:
    DBConn();

    ~DBConn();

    bool createConnection();

private:
    ReadConfig *readConfig;
    QString serverip;
    QString dbname;
    QString username;
    QString password;
};

#endif // DBCONN_H
