#ifndef READCONFIG_H
#define READCONFIG_H

#include <QString>
#include <QFile>
#include <QDomDocument>
#include <QtDebug>

/**
 * @author: Ethan
 * @date: 2013-3-20
 */
class ReadConfig
{
public:
    ReadConfig(const QString &fileName);

    ~ReadConfig();

    /**
     * 获取配置文件中的值
     *
     * @param key 配置的键
     * @param type 类型标签
     *
     * @return 配置项对应的值
     */
    QString getValue(const QString &node);

private:
    QFile *file;
    QDomDocument *doc;

};

#endif // READCONFIG_H
