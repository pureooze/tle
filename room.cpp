#include "room.h"
#include <QDebug>
#include <QMap>
#include <QString>

Room::Room()
{
    qDebug() << "created";
}


void Room::addPortal(QString name, QString id)
{
/*
    Function: Add a new portal to the QMap that contains
    a list of the possible portal.
    Requires: QString, QString
    Returns: void
    Author: Uzair Shamim
*/

    qDebug() << "Attempting to add portal" << name << "with room" << id;
    portals.insertMulti(name, id);
}

void Room::removePortal(QString name)
{
/*
    Function: Remove a portal from the QMap that contains
    a list of the possible portal.
    Requires: QString
    Returns: void
    Author: Uzair Shamim
*/
    qDebug() << "Attempting to remove portal" << name;
    portals.remove(name);
}

void Room::displayPortals()
{
/*
    Function: Display all the portals for the room
    Requires: void
    Returns: void
    Author: Uzair Shamim
*/
    qDebug() << portals;
}

QMap<QString, QString> Room::getPortals()
{
    return portals;
}
