#ifndef OBJECT_H
#define OBJECT_H
#include <QMap>
#include <QString>
#include <QStringList>

class object
{
public:
    object(QStringList params);
    QMap<QString, QString> attributes;

    QString name;
    QString textGlance;
    QString textExamine;
    QString errorExamine;
    QString errorUse;
    QString errorTake;
    QString errorDrop;

    QStringList triggers;
    QStringList eventsGlance;
    QStringList eventsExamine;
    QStringList eventsUse;
    QStringList eventsTake;
    QStringList eventsDrop;

    bool allowGlance;
    bool allowExamine;
    bool allowUse;
    bool allowTake;
    bool allowDrop;
};

#endif // OBJECT_H
