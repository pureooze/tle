#include "events.h"
#include <QDebug>

events::events()
{
}

void events::printData(QMap<QString, QString> obj)
{
    attributes.insert("abc", obj);
    qDebug() << attributes;
}
