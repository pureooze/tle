#include "editor.h"
#include "ui_editor.h"
#include "room.h"
#include "roomgui.h"
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
    dataRoom = new Room();
    Room *twoRoom = new Room();
    rooms->insert("Desert", dataRoom);
    rooms->insert("Cave", twoRoom);
    guiRoom = new RoomGUI();
    scene->addItem(guiRoom);
}

void editor::on_addExit_clicked()
{
    promptWindow = new prompterAddExit;
    promptWindow->setModal(true);
    connect(promptWindow, SIGNAL(addExit(const QString &, const QString &, const QString &)), this,\
            SLOT(dialogAddExitConfirmed(const QString &, const QString &, const QString &)));
    promptWindow->setMap(rooms);
    promptWindow->exec();
}

void editor::on_removeExit_clicked()
{
    QString portalName = "caveEntrance";
    rooms->value("Forest")->removePortal(portalName);
}

void editor::on_deleteRoom_clicked()
{
    mode = "deleteRoom";
}

void editor::sceneClicked()
{
    // Determine what should be done on mouse click, depending on the mode
    if(mode == "deleteRoom"){

        /*

        Get the point in the global scope and translate it to the
        scene's scope. This allows us to easily delete objects
        without having to manually translate. Particularly useful
        when the origin on the scene has been moved.

        */

        qDebug() << "Mode is" << mode;
        QPoint origin = ui->graphicsView->mapFromGlobal(QCursor::pos());
        QPointF relativeOrigin = ui->graphicsView->mapToScene(origin);
        scene->removeItem(scene->itemAt(relativeOrigin, QTransform()));
        mode = "normal";
    }else{
        qDebug() << "Mode is" << mode;
    }
}

//void editor::dialogConfirmed()
//{
//    qDebug() << "pressed";
//    dataRoom = new Room();
//    rooms->insert("Forest", dataRoom);
//    guiRoom = new RoomGUI();
//    scene->addItem(guiRoom);
//}

void editor::dialogAddExitConfirmed(QString roomName, QString exitName, QString target)
{
    qDebug() << "new exits recieved";
    rooms->value(roomName)->addPortal(exitName, target);
    rooms->value(roomName)->displayPortals();
}
