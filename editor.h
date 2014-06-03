#ifndef EDITOR_H
#define EDITOR_H

#include "room.h"
#include "scene.h"
#include "events.h"
#include "object.h"
#include "prompterAddExit.h"
#include "addobjectdialog.h"
#include "addeventdialog.h"

#include <QMainWindow>
#include <QMap>
#include <QGraphicsScene>
#include <QString>

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

    void on_addObject_pressed();

    void on_addEvent_pressed();

private:
    Ui::editor *ui;
    Scene *scene;
    Room *dataRoom;
    object *obj;
    QMap<QString, Room *> *rooms;
    QString mode = "normal";
    QString selectedRoom = "";
    prompterAddExit *promptAddExitWindow;
    addObjectDialog *addObjectDialogWindow;
    addEventDialog *addEventDialogWindow;
    int roomCount = 0;

protected:
    //void paintEvent(QPaintEvent *e);

public slots:
    void sceneClicked();
    void dialogAddExitConfirmed(QString roomName, QString portalName, QString target);
    void dialogRemoveExitConfirmed(QString roomName, QString portalName);
    void removalCleanup(QString name);
    void createObject(QStringList objParams);
    void createEvent(QStringList eventParams);

signals:
    void createRoomSig();
    void setRoomMap(QMap<QString,Room*>);
    void removeExits(QString);
    void callExitRemoval(QString, QString);
    void displayAttributes(QString);
    void changeListSelection(QString);
};

#endif // EDITOR_H
