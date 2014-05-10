#ifndef EDITOR_H
#define EDITOR_H

#include "room.h"
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
    void createRoom();
    void on_addExit_clicked();
    void on_removeExit_clicked();
    //void removeRoom();
    void addPortalsListView(QMap<QString, QString> portals);
    void on_roomListWidget_clicked(const QModelIndex &index);
    void on_actionCreateRoom_triggered();
    void on_actionDeleteRoom_triggered();
    void changeRoomListSelection(QString name);

    void on_lineEdit_returnPressed();

private:
    Ui::editor *ui;
    Scene *scene;
//    RoomGUI *guiRoom;
    Room *dataRoom;
    QMap<QString, Room *> *rooms;
    QString mode = "normal";
    QString selectedRoom = "";
    prompterCreateRoom *promptCreateRoomWindow;
    prompterAddExit *promptAddExitWindow;
    prompterRemoveExit *promptRemoveExitWindow;
    int roomCount = 0;

protected:
    //void paintEvent(QPaintEvent *e);

public slots:
    void sceneClicked();
    void dialogAddExitConfirmed(QString roomName, QString portalName, QString target);
    void dialogRemoveExitConfirmed(QString roomName, QString portalName);
    void removalCleanup(QString name);

signals:
    void createRoomSig();
    void setRoomMap(QMap<QString,Room*>);
    void removeExits(QString);
    void callExitRemoval(QString, QString);
    void displayPortals(QMap<QString, QString> );
    void changeListSelection(QString);
};

#endif // EDITOR_H
