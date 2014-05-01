#ifndef ROOM_H
#define ROOM_H

#include <QMap>
#include <QString>
#include <QDebug>
#include <QPainter>
#include <QGraphicsItem>

class Room : public QGraphicsItem
{
public:
    Room();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void addPortal(QString name, QString id);
    void removePortal(QString name);
    void displayPortals();
    void setName(QString name);

    bool pressed;
    QMap<QString, QString> getPortals();
    QRectF boundingRect() const;
    QString name;

private:
    QMap<QString,QString> portals;

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
};

#endif // ROOM_H
