#ifndef OBJECT_H
#define OBJECT_H
#include <QMap>
#include <QString>

class object
{
public:
    object(QStringList params);
    QMap<QString, QString> attributes;
};

#endif // OBJECT_H
