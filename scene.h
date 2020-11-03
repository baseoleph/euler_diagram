#ifndef SCENE_H
#define SCENE_H

#include <QGraphicsScene>
#include <QObject>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <QSet>
#include <QGraphicsEllipseItem>
#include <QtMath>


class Scene : public QGraphicsScene
{
    Q_OBJECT
public:
    Scene();
    ~Scene();

    void setCircles(QSet<int> A, QSet<int> B, QSet<int> C);
    void putOneRelatOther(QGraphicsEllipseItem *one, const QGraphicsEllipseItem *oth,
                          const QSet<int> set_one, const QSet<int> set_oth);
private:
    QGraphicsEllipseItem *Ael;
    QGraphicsEllipseItem *Bel;
    QGraphicsEllipseItem *Cel;
    QSet<int> A;
    QSet<int> B;
    QSet<int> C;
};

#endif // SCENE_H

