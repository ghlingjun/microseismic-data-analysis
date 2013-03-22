#include "dbconn.h"

#include <QMessageBox>
#include <QCoreApplication>
#include <QDir>

/**
 * @author: Ethan
 * @date: 2013-3-20
 */
DBConn::DBConn()
{
//    QString fileName = ":/conn.xml";
    qDebug() << QCoreApplication::applicationDirPath();
    qDebug() << QDir::currentPath();
    QString fileName = QCoreApplication::applicationDirPath() + "/config/dbconn.xml";
    readConfig = new ReadConfig(fileName);

    serverip = readConfig->getValue("serverip");
    dbname = readConfig->getValue("dbname");
    username = readConfig->getValue("username");
    password = readConfig->getValue("password");
}

bool DBConn::createConnection()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName(serverip);
    db.setDatabaseName(dbname);
    db.setUserName(username);
    db.setPassword(password);
    if (!db.open()) {
        const QString content = "Unable to establish a database connection.\n"
                                "Please make sure the server is up.\n"
                                "And check your host name: " + serverip;
        QMessageBox::critical(0,
                              "Cannot open database",
                              content,
                              QMessageBox::Ok);
        return false;
    }
    return true;
}
