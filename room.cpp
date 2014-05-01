#include "room.h"
#include <QDebug>
#include <QMap>
#include <QString>

Room::Room()
{
    pressed = false;
    setFlag(ItemIsMovable);
    test = "aaaaaaaaaa";
}

void Room::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRectF rec = boundingRect();
    QBrush brush(Qt::blue);

    if(pressed){
        brush.setColor(Qt::red);
    }else{
        brush.setColor(Qt::green);
    }

    painter->fillRect(rec, brush);
    painter->drawRect(rec);
}

QRectF Room::boundingRect() const
{
    return QRectF(0, 0, 100, 100);
}

void Room::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    pressed = true;
    update();
    QGraphicsItem::mousePressEvent(event);
}

void Room::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    pressed = false;
    update();
    QGraphicsItem::mouseReleaseEvent(event);
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
