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

void Scene::setCircles(QSet<int> A, QSet<int> B, QSet<int> C, int categ)
{
    this->A = A;
    this->B = B;
    this->C = C;

    Ael->setPen(QPen(Qt::darkRed));
    Bel->setPen(QPen(Qt::darkGreen));
    Cel->setPen(QPen(Qt::darkBlue));

         if (categ == 1) cat1();
    else if (categ == 2) cat2();
    else if (categ == 3) cat3();
    else if (categ == 4) cat4();
    else if (categ == 5) cat5();
    else if (categ == 6) cat6();
    else if (categ == 7) cat7();
    else if (categ == 8) cat8();
    else if (categ == 9) cat9();
    else if (categ == 10) cat10();
    else if (categ == 12) cat12();
    else if (categ == 13) cat13();
    else if (categ == 14) cat14();
    else if (categ == 15) cat15();
    else if (categ == 16) cat16();
}

void Scene::cat1()
{

}

void Scene::cat2()
{

}

void Scene::cat3()
{

}

void Scene::cat4()
{

}

void Scene::cat5()
{

}

void Scene::cat6()
{

}

void Scene::cat7()
{

}

void Scene::cat8()
{

}

void Scene::cat9()
{

}

void Scene::cat10()
{

}

void Scene::cat12()
{

}

void Scene::cat13()
{

}

void Scene::cat14()
{

}

void Scene::cat15()
{

}

void Scene::cat16()
{

}
