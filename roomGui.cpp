#include "roomGui.h"
#include <QPainter>

RoomGUI::RoomGUI()
{
    pressed = false;
    setFlag(ItemIsMovable);
}

void RoomGUI::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
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

QRectF RoomGUI::boundingRect() const
{
    return QRectF(0, 0, 100, 100);
}

void RoomGUI::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    pressed = true;
    update();
    QGraphicsItem::mousePressEvent(event);
}

void RoomGUI::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    pressed = false;
    update();
    QGraphicsItem::mouseReleaseEvent(event);
}
