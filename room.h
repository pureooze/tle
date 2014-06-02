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
    void setGlance(QString glanceContent);
    void setExamine(QString examineContent);

    bool pressed;
    QMap<QString, QString> getPortals();
    QString getGlance();
    QString getExamine();
    QStringList getItems();
    QStringList getActors();
    QRectF boundingRect() const;

    QString name;
    QString textGlance;
    QString textExamine;
    QStringList containItems;
    QStringList containActors;

private:
    QMap<QString,QString> portals;

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
};

#endif // ROOM_H
