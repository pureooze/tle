#include "object.h"
#include <QStringList>
#include <QDebug>

object::object(QStringList params)
{
    this->name = params[0];
    qDebug() << this->name;
}
