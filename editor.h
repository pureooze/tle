#ifndef EDITOR_H
#define EDITOR_H

#include "room.h"
#include "roomgui.h"
#include "scene.h"
#include <QMainWindow>
#include <QMap>
#include <QtCore>
#include <QtGui>

namespace Ui {
class editor;
}

class editor : public QMainWindow
{
    Q_OBJECT

public:
    explicit editor(QWidget *parent = 0);
    ~editor();

private slots:
    void on_addExit_clicked();
    void on_createRoom_clicked();
    void on_removeExit_clicked();
    void on_deleteRoom_clicked();
    //void removeRoom();

private:
    Ui::editor *ui;
    QMap<QString, Room *> *maps;
    Scene *scene;
    RoomGUI *guiRoom;
    Room *dataRoom;
    QString mode = "normal";

protected:
    //void paintEvent(QPaintEvent *e);

public slots:
    void sceneClicked();
};

#endif // EDITOR_H
