#ifndef EDITOR_H
#define EDITOR_H

#include "room.h"
#include "roomGui.h"
#include "scene.h"
#include "prompterCreateRoom.h"
#include "prompterAddExit.h"
#include "prompterRemoveExit.h"
#include <QMainWindow>
#include <QMap>
#include <QGraphicsScene>

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
    Scene *scene;
//    RoomGUI *guiRoom;
    Room *dataRoom;
    QMap<QString, Room *> *rooms;
    QString mode = "normal";
    prompterCreateRoom *promptCreateRoomWindow;
    prompterAddExit *promptAddExitWindow;
    prompterRemoveExit *promptRemoveExitWindow;

protected:
    //void paintEvent(QPaintEvent *e);

public slots:
    void sceneClicked();
    void dialogCreateRoomConfirmed(QString roomName);
    void dialogAddExitConfirmed(QString roomName, QString portalName, QString target);
    void dialogRemoveExitConfirmed(QString roomName, QString portalName);

signals:
    void setRoomMap(QMap<QString,Room*>);
};

#endif // EDITOR_H
