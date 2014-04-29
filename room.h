#ifndef ROOM_H
#define ROOM_H

#include <QMap>
#include <QString>
#include <QPainter>
#include <QGraphicsItem>
#include <QDebug>

class Room
{
public:
    Room();
    void addPortal(QString name, int id);
    void removePortal(QString name);
    void displayPortals();

private:
    QString title;
    QMap<QString,int> portals;
};

#endif // ROOM_H
