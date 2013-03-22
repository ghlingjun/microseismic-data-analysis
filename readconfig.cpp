#include "readconfig.h"

#include <QMessageBox>

/**
 * @author: Ethan
 * @date: 2013-3-20
 */
ReadConfig::ReadConfig(const QString &fileName)
{
    file = new QFile(fileName);
    if(!file->open(QFile::ReadOnly | QFile::Text))
    {
        QMessageBox::critical(0,
                              "Load XML File Problem",
                              "Couldn't open xml file to load settings for database",
                              QMessageBox::Ok);
        return;
    }

    doc = new QDomDocument();
    if(!doc->setContent(file))
    {
        file->close();
        return;
    }
}

ReadConfig::~ReadConfig()
{
    delete file;
    file = 0;
    delete doc;
    doc = 0;
}

QString ReadConfig::getValue(const QString &nodeName)
{
    QString result = "";
    QDomElement docElem = doc->documentElement();  // 返回根元素
    QDomNode n = docElem.firstChild();   // 返回根节点的第一个子节点

    while(!n.isNull()) // 如果节点不为空
    {
        if (n.isElement())  //如果节点是元素
        {
            QDomElement e = n.toElement();  //将其转换为元素
            // 返回元素标记
            qDebug() << qPrintable(e.tagName());
                   // << qPrintable(e.attribute("id")); // 返回元素id属性的值
            QDomNodeList list = e.childNodes(); // 获得元素 e 的所有子节点的列表
            for(int i=0; i<list.count(); i++) // 遍历该列表
            {
                QDomNode node = list.at(i);
                if(node.isElement())
                {
                    qDebug() << " " << qPrintable(node.toElement().tagName())
                            << qPrintable(node.toElement().text());
                    if(nodeName.operator ==(node.toElement().tagName()))
                    {
                        result = node.toElement().text();
                        break;
                    }
                }
            }
        }
        n = n.nextSibling(); // 下一个兄弟节点
    }

    return result;
}
