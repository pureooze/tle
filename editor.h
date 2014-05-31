#ifndef EDITOR_H
#define EDITOR_H

#include "room.h"
#include "scene.h"
#include "prompterAddExit.h"
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
    void addAttrListView(QString name);
    void on_roomListWidget_clicked(const QModelIndex &index);
    void on_actionCreateRoom_triggered();
    void on_actionDeleteRoom_triggered();
    void changeRoomListSelection(QString name);

    void on_lineEdit_returnPressed();

    void on_tableWidget_cellClicked(int row, int column);

    void on_paramEditWidget_textChanged();

private:
    Ui::editor *ui;
    Scene *scene;
//    RoomGUI *guiRoom;
    Room *dataRoom;
    QMap<QString, Room *> *rooms;
    QString mode = "normal";
    QString selectedRoom = "";
    prompterAddExit *promptAddExitWindow;
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
    void displayAttributes(QString);
    void changeListSelection(QString);
};

#endif // EDITOR_H
