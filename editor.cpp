#include "editor.h"
#include "ui_editor.h"
#include "room.h"
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
    connect(this, SIGNAL(removeExits(QString)), this, SLOT(removalCleanup(QString)));
    connect(this, SIGNAL(callExitRemoval(QString,QString)), this, \
            SLOT(dialogRemoveExitConfirmed(QString,QString)));
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
    Function: Get the point in the QWidget scope and translate it to the
    scene's scope. This allows us to easily delete objects without having
    to manually translate. Particularly useful when the origin on the
    scene has been moved (which *will* happen) as the objects move around.

    Requires: void
    Returns: void
    Author: Uzair Shamim
*/
    qDebug() << "Mode is" << mode;
    // Determine what should be done on mouse click, depending on the mode
    if(mode == "deleteRoom"){
        QPoint origin = ui->graphicsView->mapFromGlobal(QCursor::pos());
        QPointF relativeOrigin = ui->graphicsView->mapToScene(origin);
        // Avoid segfault by making sure there is a room being clicked
        if(scene->itemAt(relativeOrigin, QTransform())){
            Room *room = (Room *)scene->itemAt(relativeOrigin, QTransform());
            emit removeExits(room->name);
            rooms->remove(room->name);
            scene->removeItem(scene->itemAt(relativeOrigin, QTransform()));
            mode = "normal";
        }
    }else{
        ;;
    }
}

void editor::removalCleanup(QString name)
{
    qDebug() << "removalCleanup: name recieved";
    for(auto i: rooms->value(name)->getPortals()){
        QString portal = rooms->value(name)->getPortals().key(i);
        emit callExitRemoval(i, portal);
    }
    qDebug() << "removalCleanup: completed";
}


void editor::dialogCreateRoomConfirmed(QString roomName)
{
/*
    Function: When a user clicks the Create Room button, the slot for the
    button click emits a signal that is connected to this function. Use
    the Room class to create an object and then pass it's location to a
    QMap. Then pass the Room object to the QGraphicsScene to display.

    Requires: QString
    Returns: void
    Author: Uzair Shamim
*/
    qDebug() << "dialogCreateRoomConfirmed: new room recieved";
    dataRoom = new Room();
    rooms->insert(roomName, dataRoom);
    dataRoom->setName(roomName);
    scene->addItem(dataRoom);
    qDebug() << "dialogCreateRoomConfirmed: room created, function end";
}

void editor::dialogAddExitConfirmed(QString roomName, QString portalName, QString target)
{
/*
    Function: When a user clicks the Add Exit button, the slot for the
    buttons click state emits a signal that is connected to this function.
    Use the QMap rooms that contains all the Room objects and call its
    function addPortal. Then switch the target and roomName so that both
    the target and room referenced by roomName are linked to each other.

    Requires: QString, QString, QString
    Returns: void
    Author: Uzair Shamim
*/
    qDebug() << "dialogAddExitConfirmed: new portal recieved";
    rooms->value(roomName)->addPortal(portalName, target);
    rooms->value(target)->addPortal(portalName, roomName);
    qDebug() << "dialogAddExitConfirmed: portal added, function end";
}

void editor::dialogRemoveExitConfirmed(QString roomName, QString portalName)
{
/*
    Function: When a user clicks the Remove Exit button, the slot for the
    buttons click state emits a signal that is connected to this function.
    Use the QMap rooms to access the Room objects and call their method
    getPortals, filtering for the room that is the target of the portal
    referenced by portalName. Then remove both rooms using removePortal.

    Requires: QString, QString
    Returns: void
    Author: Uzair Shamim
*/
    qDebug() << "dialogRemoveExitConfirmed: portal to remove recieved";
    QString otherRoom = rooms->value(roomName)->getPortals().value(portalName);
    rooms->value(roomName)->removePortal(portalName);
    rooms->value(otherRoom)->removePortal(portalName);
    qDebug() << "dialogRemoveExitConfirmed: portal removed, function end";
}






/*
 * BEWARE ALL WHO ENTER HERE
 *
 * THIS IS LAND OF THE DEADLY COMMENTED CODE
 *
 * THERE IS NO GUARANTEE THIS CODE WILL WORK
 * IN FACT IT PROBABLY WONT SO DONT TRY IT
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
