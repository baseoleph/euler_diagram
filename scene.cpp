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
    int rad = 200;
    Ael->setPen(QPen(Qt::darkRed));
    Ael->setPos(0, 0);
    Ael->setRect(0, 0, rad, rad);
    Ael->moveBy(-rad/2, -rad/2);

    Bel->setPen(QPen(Qt::darkGreen));
    Bel->setPos(0, 0);
    Bel->setRect(0, 0, rad, rad);
    Bel->moveBy(-rad/2, -rad/2);

    Cel->setPen(QPen(Qt::darkBlue));
    Cel->setPos(0, 0);
    Cel->setRect(0, 0, rad, rad);
    Cel->moveBy(-rad/2, -rad/2);

    putOneRelatOther(Bel, Ael, B, A);
    putOneRelatOther(Cel, Bel, C, B);
    putOneRelatOther(Cel, Ael, C, A);
}

void Scene::putOneRelatOther(QGraphicsEllipseItem *one, const QGraphicsEllipseItem *oth,
                             const QSet<int> set_one, const QSet<int> set_oth)
{
//    if (not set_one->intersects(*set_oth))
//    {
//        one->moveBy(oth->boundingRect().width() + 10, 0);
//    }
    if (set_one == set_oth)
    {
        one->setPos(oth->pos());
        one->setRect(oth->rect());
    }
    else if (set_oth.contains(set_one) && not set_one.contains(set_oth))
    {
        one->moveBy(one->boundingRect().width()/4, one->boundingRect().height()/4);
        one->setRect(0, 0, one->boundingRect().width()/2, one->boundingRect().height()/2);
    }
    else if (not set_oth.contains(set_one) && set_one.contains(set_oth))
    {
        one->moveBy(-one->boundingRect().width()/2, -one->boundingRect().height()/2);
        one->setRect(0, 0, one->boundingRect().width()*2, one->boundingRect().height()*2);
    }
    else if (not set_one.intersects(set_oth))
    {
        one->moveBy(oth->boundingRect().width() + 10, 0);
    }
    else
    {
        one->moveBy(oth->boundingRect().width()/2, 0);
    }
}
