#include "editor.h"
#include "ui_editor.h"
#include "room.h"
#include "roomGui.h"
#include "scene.h"
#include "prompterAddExit.h"
#include <QDebug>
#include <QList>

editor::editor(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::editor)
{
    ui->setupUi(this);
    setMouseTracking(true);

    scene = new Scene();
    ui->graphicsView->setScene(scene);
    connect(scene, SIGNAL(roomSelected()), this, SLOT(sceneClicked()));
    rooms = new QMap<QString, Room *>;
}

editor::~editor()
{
    delete ui;
}

void editor::on_createRoom_clicked()
{
    qDebug() << "pressed";
    promptCreateRoomWindow = new prompterCreateRoom;
    promptCreateRoomWindow->setModal(true);
    connect(promptCreateRoomWindow, SIGNAL(createRoom(QString)), this,\
            SLOT(dialogCreateRoomConfirmed(QString)));
    promptCreateRoomWindow->exec();
}

void editor::on_addExit_clicked()
{
    promptAddExitWindow = new prompterAddExit;
    promptAddExitWindow->setModal(true);
    connect(promptAddExitWindow, SIGNAL(addExit(QString, QString, QString)), this,\
            SLOT(dialogAddExitConfirmed(QString, QString, QString)));
    promptAddExitWindow->setMap(rooms);
    promptAddExitWindow->exec();
}

void editor::on_removeExit_clicked()
{
    promptRemoveExitWindow = new prompterRemoveExit;
    promptRemoveExitWindow->setModal(true);
    //promptRemoveExitWindow->setMap(rooms);
    connect(promptRemoveExitWindow, SIGNAL(removeExit(QString,QString)), this,\
            SLOT(dialogRemoveExitConfirmed(QString,QString)));
    connect(this, SIGNAL(setRoomMap(QMap<QString,Room*>)), promptRemoveExitWindow,\
            SLOT(setMap(QMap<QString,Room*>)));
    emit setRoomMap(*rooms);
    promptRemoveExitWindow->exec();
}

void editor::on_deleteRoom_clicked()
{
    mode = "deleteRoom";
}

void editor::sceneClicked()
{
/*

Get the point in the global scope and translate it to the
scene's scope. This allows us to easily delete objects
without having to manually translate. Particularly useful
when the origin on the scene has been moved (which *will* happen).

*/

    // Determine what should be done on mouse click, depending on the mode
    if(mode == "deleteRoom"){
        qDebug() << "Mode is" << mode;
        QPoint origin = ui->graphicsView->mapFromGlobal(QCursor::pos());
        QPointF relativeOrigin = ui->graphicsView->mapToScene(origin);
        scene->removeItem(scene->itemAt(relativeOrigin, QTransform()));
        mode = "normal";
    }else{
        qDebug() << "Mode is" << mode;
    }
}

void editor::dialogCreateRoomConfirmed(QString roomName)
{
    qDebug() << "dialogCreateRoomConfirmed: new room recieved";
    dataRoom = new Room();
    rooms->insert(roomName, dataRoom);
    guiRoom = new RoomGUI();
    scene->addItem(guiRoom);
    qDebug() << "dialogCreateRoomConfirmed: room created, function end";
}

void editor::dialogAddExitConfirmed(QString roomName, QString portalName, QString target)
{
    qDebug() << "dialogAddExitConfirmed: new portal recieved";
    rooms->value(roomName)->addPortal(portalName, target);
    qDebug() << "dialogAddExitConfirmed: portal added, function end";
}

void editor::dialogRemoveExitConfirmed(QString roomName, QString portalName)
{
    qDebug() << "dialogRemoveExitConfirmed: portal to remove recieved";
    rooms->value(roomName)->removePortal(portalName);
    qDebug() << "dialogRemoveExitConfirmed: portal removed, function end";
}







/*
 * BEWARE ALL WHO ENTER HERE
 *
 * THIS IS LAND OF THE DEADLY COMMENTED CODE
 *
*/

//void editor::dialogConfirmed()
//{
//    qDebug() << "pressed";
//    dataRoom = new Room();
//    rooms->insert("Forest", dataRoom);
//    guiRoom = new RoomGUI();
//    scene->addItem(guiRoom);
//}
