#ifndef SCENE_H
#define SCENE_H

#include <QGraphicsScene>
#include <QObject>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <QSet>
#include <QGraphicsEllipseItem>
#include <QtMath>
#include <QRandomGenerator>

#include "filledpath.h"

class Scene : public QGraphicsScene
{
    Q_OBJECT
public:
    Scene();
    ~Scene();

    void colorize(QSet<int> D);
    void setCircles(QSet<int> A, QSet<int> B, QSet<int> C, int categ);
    void putOneRelatOther(QGraphicsEllipseItem *one, const QGraphicsEllipseItem *oth,
                          QSet<int> set_one, const QSet<int> set_oth);

signals:
    void signalForMoveText();

private:
    FilledPath *fp;

    void moveText();
    int categ;
    int cell;
    int mainwidth;
    QGraphicsTextItem *At;
    QGraphicsTextItem *Bt;
    QGraphicsTextItem *Ct;
    QGraphicsEllipseItem *Ael;
    QGraphicsEllipseItem *Bel;
    QGraphicsEllipseItem *Cel;
    QSet<int> A;
    QSet<int> B;
    QSet<int> C;

    void cat1();
    void cat2();
    void cat3();
    void cat4();
    void cat5();
    void cat6();
    void cat7();
    void cat8();
    void cat9();
    void cat10();
    void cat12();
    void cat13();
    void cat14();
    void cat15();
    void cat16();


    int mainx;
    int mainy;
    int mainshift;
};

#endif // SCENE_H

