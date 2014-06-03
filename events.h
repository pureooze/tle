#ifndef EVENTS_H
#define EVENTS_H
#include <QMap>
#include <QList>
#include <QString>

class events
{
public:
    events();
    QMap<QString, QMap<QString, QString> > attributes;

    void printData(QString name, QMap<QString, QString> obj);

private:
};

#endif // EVENTS_H
