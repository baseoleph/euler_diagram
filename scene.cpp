#include "scene.h"

Scene::Scene()
{
    Ael = new QGraphicsEllipseItem();
    Bel = new QGraphicsEllipseItem();
    Cel = new QGraphicsEllipseItem();

    addItem(Ael);
    addItem(Bel);
    addItem(Cel);
}

Scene::~Scene()
{
   delete Ael;
   delete Bel;
   delete Cel;
}

void Scene::setCircles(QSet<int> A, QSet<int> B, QSet<int> C)
{
    this->A = A;
    this->B = B;
    this->C = C;
    int width = this->width();
    int height = this->height();
    int cnt = A.size() + B.size() + C.size();
    cell = width / cnt;

    int dima = A.size() * cell;
    Ael->setPen(QPen(Qt::darkRed));
    Ael->setPos(0, height/2 - dima/2);
    Ael->setRect(0, 0, dima, dima);
//    Ael->moveBy(-rada/2, -rada/2);

    int dimb = B.size() * cell;
    Bel->setPen(QPen(Qt::darkGreen));
    Bel->setPos(Ael->boundingRect().width(), height/2 - dimb/2);
    Bel->setRect(0, 0, dimb, dimb);
//    Bel->moveBy(-radb/2, -radb/2);


    putOneRelatOther(Bel, Ael, B, A);

//    int rightA = Ael->pos().x() + Ael->boundingRect().width();
//    int rightB = Bel->pos().x() + Bel->boundingRect().width();

//    int radc = C.size() * 10;
//    Cel->setPen(QPen(Qt::darkBlue));
//    Cel->setPos(qMax(rightA, rightB) + 10, 0);
//    Cel->setRect(0, 0, radc, radc);
//    Cel->moveBy(0, -radc/2);
//    putOneRelatOther(Cel, Bel, C, B);
//    putOneRelatOther(Cel, Ael, C, A);
}

void Scene::putOneRelatOther(QGraphicsEllipseItem *one, const QGraphicsEllipseItem *oth,
                              QSet<int> set_one, const QSet<int> set_oth)
{
    if (set_one == set_oth)
    {
        one->setPos(oth->pos());
    }
    else if (set_oth.contains(set_one) && not set_one.contains(set_oth))
    {
        one->moveBy(-oth->rect().width(), 0);
    }
    else if (not set_oth.contains(set_one) && set_one.contains(set_oth))
    {
        one->moveBy(-oth->rect().width(), 0);
    }
    else if (set_one.intersects(set_oth))
    {
        one->moveBy(-cell * set_one.intersect(set_oth).size(), 0);
    }
}
