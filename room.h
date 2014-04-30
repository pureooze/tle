#ifndef ROOM_H
#define ROOM_H

#include <QMap>
#include <QString>
#include <QDebug>

class Room
{
public:
    Room();
    void addPortal(QString name, QString id);
    void removePortal(QString name);
    void displayPortals();
    QMap<QString, QString> getPortals();

private:
    QString title;
    QMap<QString,QString> portals;
};

#endif // ROOM_H
