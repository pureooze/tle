#include "editor.h"
#include "ui_editor.h"
#include "room.h"
#include "roomgui.h"
#include "scene.h"
#include "QDebug"
#include <QMap>

editor::editor(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::editor)
{
    ui->setupUi(this);
    setMouseTracking(true);

    scene = new Scene();
    ui->graphicsView->setScene(scene);
    connect(scene, SIGNAL(roomSelected()), this, SLOT(sceneClicked()));
    maps = new QMap<QString, Room *>;
}

editor::~editor()
{
    delete ui;
}

//void editor::paintEvent(QPaintEvent *e)
//{
//    QPainter painter(this);

//    //make polygon
//    QPolygon poly;
//    poly << QPoint(10, 10);
//    poly << QPoint(10, 100);
//    poly << QPoint(100, 10);
//    poly << QPoint(100, 100);

//    //make pen
//    QPen linepen;
//    linepen.setWidth(8);
//    linepen.setColor(Qt::blue);
//    linepen.setJoinStyle(Qt::MiterJoin);
//    painter.setPen(linepen);

//    //make brush
//    QBrush fillbrush;
//    fillbrush.setColor(Qt::green);
//    fillbrush.setStyle(Qt::SolidPattern);

//    //Fill the polygon
//    QPainterPath path;
//    path.addPolygon(poly);

//    //draw polygon
//    painter.drawPolygon(poly);
//    painter.fillPath(path, fillbrush);
//}

void editor::on_createRoom_clicked()
{
    guiRoom = new RoomGUI();
    dataRoom = new Room();
    maps->insert("1", dataRoom);
    dataRoom->addPortal("dave", 2);
    scene->addItem(guiRoom);
    Room *test = maps->value(0);
}

void editor::on_addExit_clicked()
{
    QString portalName = "caveEntrance";
    int portalToRoom = 4;
    //qDebug() << maps;
}

void editor::on_removeExit_clicked()
{
    //QString portalName = "cave";
    //maps[1].removePortal(portalName);
}

void editor::on_deleteRoom_clicked()
{
    qDebug() << scene->items();
    qDebug() << scene->itemAt(this->mapFromGlobal(QCursor::pos()), QTransform());
    mode = "deleteRoom";
}

void editor::sceneClicked()
{
    // Determine what should be done on mouse click, depending on the mode
    if(mode == "deleteRoom"){
        qDebug() << "Mode is" << mode;

        /*
         * Get the point in the global scope and translate it to the
         *  scene's scope. This allows us to easily delete objects
         *  without having to manually translate. Particularly useful
         *  when the origin on the scene has been moved.
         */
        QPoint origin = ui->graphicsView->mapFromGlobal(QCursor::pos());
        QPointF relativeOrigin = ui->graphicsView->mapToScene(origin);
        scene->removeItem(scene->itemAt(relativeOrigin, QTransform()));
        mode = "normal";
    }else{
        qDebug() << "Mode is" << mode;
    }
}
