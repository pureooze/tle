#ifndef ROOMGUI_H
#define ROOMGUI_H

#include <QPainter>
#include <QGraphicsItem>
#include <QDebug>

class RoomGUI : public QGraphicsItem
{
public:
    RoomGUI();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;
    bool pressed;
    QString test;

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
};

#endif // ROOMGUI_H
