#include "events.h"
#include <QDebug>

events::events()
{
}

void events::printData(QString name, QMap<QString, QString> obj)
{
    attributes.insert(name, obj);
    qDebug() << attributes;
}
