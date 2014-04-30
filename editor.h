#ifndef EDITOR_H
#define EDITOR_H

#include "room.h"
#include "roomgui.h"
#include "scene.h"
#include "prompter.h"
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
    RoomGUI *guiRoom;
    Room *dataRoom;
    QMap<QString, Room *> *rooms;
    QString mode = "normal";
    prompter *promptWindow;

protected:
    //void paintEvent(QPaintEvent *e);

public slots:
    void sceneClicked();
    void dialogConfirmed();
};

#endif // EDITOR_H
