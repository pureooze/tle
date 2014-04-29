#ifndef SCENE_H
#define SCENE_H
#include <QGraphicsScene>

class Scene : public QGraphicsScene
{
    Q_OBJECT

public:
    Scene();

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    //void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

signals:
    void roomSelected();
};

#endif // SCENE_H
