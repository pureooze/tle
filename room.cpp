#include "room.h"
#include "QDebug"
#include "QMap"
#include "QString"

Room::Room()
{
    qDebug() << "created";
}

// Function: Add a new portal to the QMap that contains
//           a list of the possible exits
// Requires: Exit Name, Room ID
// Returns: void
// Author: Uzair Shamim
void Room::addPortal(QString name, int id)
{
    qDebug() << "Attempting to add portal" << name << "with room" << id;
    portals.insertMulti(name, id);
}

void Room::removePortal(QString name)
{
    qDebug() << "Attempting to remove portal" << name;
    portals.remove(name);
}

void Room::displayPortals()
{
    qDebug() << portals["h"];
}
