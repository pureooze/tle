#include "scene.h"
#include <QDebug>
#include <QtGui>

Scene::Scene()
{
}

void Scene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    emit roomSelected();
}
