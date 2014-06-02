// A level editor/engine that can be used to generate maps for text games.
// Copyright (C) 2014 Uzair Shamim, dexgecko

// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.

#include "editor.h"
#include "ui_editor.h"
#include "room.h"
#include "scene.h"
#include "prompterAddExit.h"
#include "addobjectdialog.h"
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

    connect(this, SIGNAL(createRoomSig()), this, SLOT(createRoom()));

    connect(this, SIGNAL(changeListSelection(QString)), this,\
            SLOT(changeRoomListSelection(QString)));

    connect(this, SIGNAL(removeExits(QString)), this, SLOT(removalCleanup(QString)));

    connect(this, SIGNAL(callExitRemoval(QString,QString)), this, \
            SLOT(dialogRemoveExitConfirmed(QString,QString)));

    connect(this, SIGNAL(displayAttributes(QString)), this,\
            SLOT(addAttrListView(QString)));

    rooms = new QMap<QString, Room *>;
    ui->graphicsView->setSceneRect(0, 0, 5000, 5000);
    ui->tableWidget->setColumnCount(2);
    ui->tableWidget->setHorizontalHeaderLabels(QStringList() << "Attribute" << "Value");
    ui->tableWidget->setRowCount(7);
//    QTableWidgetItem *item = new QTableWidgetItem("ALIAS");
//    QTableWidgetItem *item2 = new QTableWidgetItem("start_room");
//    ui->tableWidget->setItem(0, 0, item);
//    ui->tableWidget->setItem(0, 1, item2);
    ui->tableWidget->resizeColumnsToContents();
}

editor::~editor()
{
    delete ui;
}

void editor::on_actionCreateRoom_triggered()
{
    qDebug() << "pressed";
    mode = "createRoom";
}

void editor::on_actionDeleteRoom_triggered()
{
    mode = "deleteRoom";
}

void editor::changeRoomListSelection(QString name)
{
    for(int i = 0; i < ui->roomListWidget->count(); i++){
        if(ui->roomListWidget->item(i)->text() == name){
            ui->roomListWidget->item(i)->setSelected(true);
            break;
        }
    }
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
//    QString name = ui->portalListWidget->currentItem()->text();
//    emit callExitRemoval(selectedRoom, name);
//    ui->portalListWidget->takeItem(ui->portalListWidget->currentRow());
}

void editor::addAttrListView(QString name)
{
    qDebug() << "addAttrListView started";
    int attrLim = 5;
    QStringList list;

    QTableWidgetItem *r0c0 = new QTableWidgetItem("ALIAS");
    QTableWidgetItem *r0c1 = new QTableWidgetItem(name);
    QTableWidgetItem *r1c0 = new QTableWidgetItem("GATES");

    for(int i = 0; i < rooms->value(name)->getPortals().keys().size(); ++i){
        QString str(rooms->value(name)->getPortals().keys()[i].constData());
        list << str;
        qDebug() << list;
    }
    QTableWidgetItem *r1c1 = new QTableWidgetItem(QString(list.join(", ")));

    QTableWidgetItem *r2c0 = new QTableWidgetItem("TEXT_GLANCE");
    QTableWidgetItem *r2c1 = new QTableWidgetItem(rooms->value(name)->getGlance());
    QTableWidgetItem *r3c0 = new QTableWidgetItem("TEXT_EXAMINE");
    QTableWidgetItem *r3c1 = new QTableWidgetItem(rooms->value(name)->getExamine());
    QTableWidgetItem *r4c0 = new QTableWidgetItem("CONTAIN_ITEMS");
    QTableWidgetItem *r4c1 = new QTableWidgetItem(rooms->value(name)->getItems().join(", "));
    QTableWidgetItem *r5c0 = new QTableWidgetItem("CONTAIN_ACTORS");
    QTableWidgetItem *r5c1 = new QTableWidgetItem(rooms->value(name)->getActors().join(", "));

    ui->tableWidget->setItem(0, 0, r0c0);
    ui->tableWidget->setItem(0, 1, r0c1);
    ui->tableWidget->setItem(1, 0, r1c0);
    ui->tableWidget->setItem(1, 1, r1c1);
    ui->tableWidget->setItem(2, 0, r2c0);
    ui->tableWidget->setItem(2, 1, r2c1);
    ui->tableWidget->setItem(3, 0, r3c0);
    ui->tableWidget->setItem(3, 1, r3c1);
    ui->tableWidget->setItem(4, 0, r4c0);
    ui->tableWidget->setItem(4, 1, r4c1);
    ui->tableWidget->setItem(5, 0, r5c0);
    ui->tableWidget->setItem(5, 1, r5c1);

    qDebug() << "addAttrListView ends";
}

void editor::on_lineEdit_returnPressed()
{
    for(int i = 0; i < ui->roomListWidget->count(); i++){
        if(ui->roomListWidget->item(i)->text() == selectedRoom){
            ui->roomListWidget->item(i)->setText(ui->lineEdit->text());
            Room *temp = rooms->value(selectedRoom);
            temp->setName(ui->lineEdit->text());
            rooms->remove(selectedRoom);
            rooms->insert(ui->lineEdit->text(), temp);
            break;
        }
    }
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
    qDebug() << selectedRoom;
    QPoint origin = ui->graphicsView->mapFromGlobal(QCursor::pos());
    QPointF relativeOrigin = ui->graphicsView->mapToScene(origin);

    // Determine what should be done on mouse click, depending on the mode
    if(mode == "deleteRoom" && scene->itemAt(relativeOrigin, QTransform())){
        Room *room = (Room *)scene->itemAt(relativeOrigin, QTransform());
        emit removeExits(room->name);
        rooms->remove(room->name);
        scene->removeItem(scene->itemAt(relativeOrigin, QTransform()));
        for(int i; i <= ui->roomListWidget->count(); i++){
            if(ui->roomListWidget->item(i)->text() == room->name){
                ui->roomListWidget->takeItem(i);
                break;
            }
        }
    }else if(mode == "createRoom"){
        emit createRoomSig();
        mode = "normal";
    }else{
        if(scene->itemAt(relativeOrigin, QTransform())){
            Room *room = (Room *)scene->itemAt(relativeOrigin, QTransform());
            selectedRoom = room->name;
            ui->scrollArea->setEnabled(true);
            ui->lineEdit->setText(room->name);
            emit changeListSelection(room->name);
            emit displayAttributes(room->name);
        }else{
            selectedRoom = "";
        }
    }
}

void editor::removalCleanup(QString name)
{
    qDebug() << "removalCleanup: name recieved";
    foreach(QString i, rooms->value(name)->getPortals()){
        qDebug() << i;
        QString portal = rooms->value(name)->getPortals().key(i);
        emit callExitRemoval(i, portal);
    }
    qDebug() << "removalCleanup: completed";
}


void editor::createRoom()
{
/*
    Function: When a user clicks the Create Room button, the slot for the
    button click emits a signal that is connected to this function. Use
    the Room class to create an object and then pass it's location to a
    QMap. Then pass the Room object to the QGraphicsScene to display.

    Requires: void
    Returns: void
    Author: Uzair Shamim
*/
    qDebug() << "dialogCreateRoomConfirmed: new room recieved";
    QPoint origin = ui->graphicsView->mapFromGlobal(QCursor::pos());
    QPointF relativeOrigin = ui->graphicsView->mapToScene(origin);

    dataRoom = new Room();
    rooms->insert("room_"+QString::number(roomCount), dataRoom);
    dataRoom->setName("room_"+QString::number(roomCount));
    scene->addItem(dataRoom);
    dataRoom->setPos(relativeOrigin);
    ui->roomListWidget->addItem("room_"+QString::number(roomCount));
    roomCount++;
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

void editor::on_roomListWidget_clicked(const QModelIndex &index)
{
    int in = ui->roomListWidget->currentRow();
    selectedRoom = ui->roomListWidget->item(in)->text();
    ui->scrollArea->setEnabled(true);
    ui->lineEdit->setText(selectedRoom);
    emit displayAttributes(selectedRoom);
}


void editor::on_tableWidget_cellClicked(int row, int column)
{
    ui->paramEditWidget->setText(ui->tableWidget->item(row, 1)->text());
}


void editor::on_paramEditWidget_textChanged()
{
    switch(ui->tableWidget->currentRow()){
    case 2:
        rooms->value(selectedRoom)->setGlance(ui->paramEditWidget->text());
        ui->tableWidget->currentItem()->setText(rooms->value(selectedRoom)->getGlance());
        break;
    case 3:
        rooms->value(selectedRoom)->setExamine(ui->paramEditWidget->text());
        ui->tableWidget->currentItem()->setText(rooms->value(selectedRoom)->getExamine());
        break;
    case 4:
        QStringList params = ui->paramEditWidget->text().split(",");
        qDebug() << params;
        ui->objectListWidget->addItem(rooms->value(selectedRoom)->getPortals()[0]);
        break;
//    default:
//        break;
    }
}

void editor::on_pushButton_pressed()
{
    // Add Object dialog
    addObjectDialogWindow = new addObjectDialog;
    addObjectDialogWindow->setModal(true);
    connect(addObjectDialogWindow, SIGNAL(objCreation(QStringList)), this, SLOT(createObject(QStringList)));
    addObjectDialogWindow->exec();
}

void editor::createObject(QStringList objParams)
{
    qDebug() << objParams;
    object obj(objParams);
}
