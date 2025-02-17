// Euler Diagram
// Copyright (C) 2020 baseoleph@gmail.com

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

#include "scene.h"

Scene::Scene()
{
    Ael = new QGraphicsEllipseItem();
    Bel = new QGraphicsEllipseItem();
    Cel = new QGraphicsEllipseItem();
    At = new QGraphicsTextItem();
    Bt = new QGraphicsTextItem();
    Ct = new QGraphicsTextItem();

    addItem(Ael);
    addItem(Bel);
    addItem(Cel);
    addItem(At);
    addItem(Bt);
    addItem(Ct);


    At->setZValue(1);
    Bt->setZValue(1);
    Ct->setZValue(1);


    At->setPlainText("A");
    Bt->setPlainText("B");
    Ct->setPlainText("C");

    fp = new FilledPath();
    addItem(fp);
    fp->setZValue(-1);

    connect(this, &Scene::signalForMoveText, this, &Scene::updateText);
}

Scene::~Scene()
{
   delete Ael;
   delete Bel;
   delete Cel;
   delete At;
   delete Bt;
   delete Ct;
   delete fp;
}

void Scene::setCircles(QSet<int> A, QSet<int> B, QSet<int> C, int categ)
{
    this->A = A;
    this->B = B;
    this->C = C;
    this->categ = categ;

    int diam = width() / 4;
    Ael->hide();
    Bel->hide();
    Cel->hide();
    At->hide();
    Bt->hide();
    Ct->hide();

    Ael->setPen(QPen("#330570"));
    Bel->setPen(QPen("#A64600"));
    Cel->setPen(QPen("#007F16"));

    Ael->setRect(0, 0, diam, diam);
    Bel->setRect(0, 0, diam, diam);
    Cel->setRect(0, 0, diam, diam);

    mainx = width()/2 - Bel->rect().width()/2;
    mainy = height()/2 - Bel->rect().width()/2;
    mainshift = width()/10;
    mainwidth = Ael->rect().width();

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
//    else qDebug() << "bad category: " << categ;
}

void Scene::updateText()
{
    At->setPlainText("A");
    Bt->setPlainText("B");
    Ct->setPlainText("C");

    if (categ >= 12 && categ <= 16)
    {
        if (A == B && B == C)
        {
            At->setPlainText("A = B = C");
            Bt->setPlainText("");
            Ct->setPlainText("");
        }
        else if (A == B)
        {
            At->setPlainText("A = B");
            Bt->setPlainText("");
        }
        else if (A == C)
        {
            At->setPlainText("A = C");
            Ct->setPlainText("");
        }
        else if (C == B)
        {
            Ct->setPlainText("B = C");
            Bt->setPlainText("");
        }
    }

    Ael->show(); Bel->show(); Cel->show();
    At->show(); Bt->show(); Ct->show();


    qreal rad;
    QPointF point;
    rad = Ael->rect().width()/2.;
    point = QPointF(Ael->rect().center().x() - rad * sqrt(2)/2 + Ael->pos().x(),
                            Ael->rect().center().y() - rad * sqrt(2)/2 + Ael->pos().y());
    At->setPos(point.x() - At->boundingRect().width(), point.y() - At->boundingRect().height());

    rad = Bel->rect().width()/2.;
    point = QPointF(Bel->rect().center().x() - rad * sqrt(2)/2 + Bel->pos().x(),
                            Bel->rect().center().y() - rad * sqrt(2)/2 + Bel->pos().y());
    Bt->setPos(point.x() - Bt->boundingRect().width(), point.y() - Bt->boundingRect().height());

    rad = Cel->rect().width()/2.;
    point = QPointF(Cel->rect().center().x() - rad * sqrt(2)/2 + Cel->pos().x(),
                            Cel->rect().center().y() - rad * sqrt(2)/2 + Cel->pos().y());
    Ct->setPos(point.x() - Ct->boundingRect().width(), point.y() - Ct->boundingRect().height());
}

void Scene::cat1()
{
    Bel->setPos(mainx, mainy);
    Ael->setPos(mainx - mainwidth - mainshift, mainy);
    Cel->setPos(mainx + mainwidth + mainshift, mainy);

    signalForMoveText();
}

void Scene::cat2()
{
    if (A.intersects(B))
    {
        Bel->setPos(mainx - mainshift, mainy);
        Ael->setPos(mainx - mainwidth, mainy);
        Cel->setPos(mainx + mainwidth, mainy);
    }
    else if (A.intersects(C))
    {
        Cel->setPos(mainx - mainshift, mainy);
        Ael->setPos(mainx - mainwidth, mainy);
        Bel->setPos(mainx + mainwidth, mainy);
    }
    else
    {
        Cel->setPos(mainx - mainshift, mainy);
        Bel->setPos(mainx - mainwidth, mainy);
        Ael->setPos(mainx + mainwidth, mainy);
    }

    signalForMoveText();
}

void Scene::cat3()
{
    if (not A.intersects(C))
    {
        Bel->setPos(mainx, mainy);
        Ael->setPos(mainx - mainwidth + mainshift/2, mainy);
        Cel->setPos(mainx + mainwidth - mainshift/2, mainy);
    }
    else if (not C.intersects(B))
    {
        Ael->setPos(mainx, mainy);
        Cel->setPos(mainx - mainwidth + mainshift/2, mainy);
        Bel->setPos(mainx + mainwidth - mainshift/2, mainy);
    }
    else
    {
        Cel->setPos(mainx, mainy);
        Bel->setPos(mainx - mainwidth + mainshift/2, mainy);
        Ael->setPos(mainx + mainwidth - mainshift/2, mainy);
    }


    signalForMoveText();
}

void Scene::cat4()
{
    Bel->setPos(mainx + mainwidth/3, mainy);
    Ael->setPos(mainx - mainwidth/3, mainy);
    Cel->setPos(mainx, mainy - mainwidth/2);

    signalForMoveText();
}

void Scene::cat5()
{
    if (B.contains(A))
    {
        Bel->setPos(mainx - mainshift, mainy);
        Ael->setRect(0, 0, mainwidth/1.7, mainwidth/1.7);
        Ael->setPos(Bel->pos().x() + mainwidth/4, Bel->pos().y() + mainwidth/4);
        Cel->setPos(mainx + mainwidth, mainy);
    }
    else if (A.contains(B))
    {
        Ael->setPos(mainx - mainshift, mainy);
        Bel->setRect(0, 0, mainwidth/1.7, mainwidth/1.7);
        Bel->setPos(Ael->pos().x() + mainwidth/4, Ael->pos().y() + mainwidth/4);
        Cel->setPos(mainx + mainwidth, mainy);
    }
    else if (A.contains(C))
    {
        Ael->setPos(mainx - mainshift, mainy);
        Cel->setRect(0, 0, mainwidth/1.7, mainwidth/1.7);
        Cel->setPos(Ael->pos().x() + mainwidth/4, Ael->pos().y() + mainwidth/4);
        Bel->setPos(mainx + mainwidth, mainy);
    }
    else if (C.contains(A))
    {
        Cel->setPos(mainx - mainshift, mainy);
        Ael->setRect(0, 0, mainwidth/1.7, mainwidth/1.7);
        Ael->setPos(Cel->pos().x() + mainwidth/4, Cel->pos().y() + mainwidth/4);
        Bel->setPos(mainx + mainwidth, mainy);
    }
    else if (B.contains(C))
    {
        Bel->setPos(mainx - mainshift, mainy);
        Cel->setRect(0, 0, mainwidth/1.7, mainwidth/1.7);
        Cel->setPos(Bel->pos().x() + mainwidth/4, Bel->pos().y() + mainwidth/4);
        Ael->setPos(mainx + mainwidth, mainy);
    }
    else if (C.contains(B))
    {
        Cel->setPos(mainx - mainshift, mainy);
        Bel->setRect(0, 0, mainwidth/1.7, mainwidth/1.7);
        Bel->setPos(Cel->pos().x() + mainwidth/4, Cel->pos().y() + mainwidth/4);
        Ael->setPos(mainx + mainwidth, mainy);
    }


    signalForMoveText();
}

void Scene::cat6()
{
    if (B.contains(A))
    {
        Bel->setPos(mainx - mainshift, mainy);
        Ael->setRect(0, 0, mainwidth/1.7, mainwidth/1.7);
        Ael->setPos(Bel->pos().x() + mainwidth/4, Bel->pos().y() + mainwidth/4);
        Cel->setPos(mainx + mainwidth/2, mainy);
    }
    else if (A.contains(B))
    {
        Ael->setPos(mainx - mainshift, mainy);
        Bel->setRect(0, 0, mainwidth/1.7, mainwidth/1.7);
        Bel->setPos(Ael->pos().x() + mainwidth/4, Ael->pos().y() + mainwidth/4);
        Cel->setPos(mainx + mainwidth/2, mainy);
    }
    else if (A.contains(C))
    {
        Ael->setPos(mainx - mainshift, mainy);
        Cel->setRect(0, 0, mainwidth/1.7, mainwidth/1.7);
        Cel->setPos(Ael->pos().x() + mainwidth/4, Ael->pos().y() + mainwidth/4);
        Bel->setPos(mainx + mainwidth/2, mainy);
    }
    else if (C.contains(A))
    {
        Cel->setPos(mainx - mainshift, mainy);
        Ael->setRect(0, 0, mainwidth/1.7, mainwidth/1.7);
        Ael->setPos(Cel->pos().x() + mainwidth/4, Cel->pos().y() + mainwidth/4);
        Bel->setPos(mainx + mainwidth/2, mainy);
    }
    else if (B.contains(C))
    {
        Bel->setPos(mainx - mainshift, mainy);
        Cel->setRect(0, 0, mainwidth/1.7, mainwidth/1.7);
        Cel->setPos(Bel->pos().x() + mainwidth/4, Bel->pos().y() + mainwidth/4);
        Ael->setPos(mainx + mainwidth/2, mainy);
    }
    else if (C.contains(B))
    {
        Cel->setPos(mainx - mainshift, mainy);
        Bel->setRect(0, 0, mainwidth/1.7, mainwidth/1.7);
        Bel->setPos(Cel->pos().x() + mainwidth/4, Cel->pos().y() + mainwidth/4);
        Ael->setPos(mainx + mainwidth/2, mainy);
    }

    signalForMoveText();
}

void Scene::cat7()
{
    if (B.contains(A))
    {
        Bel->setPos(mainx - mainshift, mainy);
        Ael->setRect(0, 0, mainwidth/1.7, mainwidth/1.7);
        Ael->setPos(Bel->pos().x() + mainwidth/4, Bel->pos().y() + mainwidth/4);
        Cel->setPos(mainx + mainwidth/4, mainy);
    }
    else if (A.contains(B))
    {
        Ael->setPos(mainx - mainshift, mainy);
        Bel->setRect(0, 0, mainwidth/1.7, mainwidth/1.7);
        Bel->setPos(Ael->pos().x() + mainwidth/4, Ael->pos().y() + mainwidth/4);
        Cel->setPos(mainx + mainwidth/4, mainy);
    }
    else if (A.contains(C))
    {
        Ael->setPos(mainx - mainshift, mainy);
        Cel->setRect(0, 0, mainwidth/1.7, mainwidth/1.7);
        Cel->setPos(Ael->pos().x() + mainwidth/4, Ael->pos().y() + mainwidth/4);
        Bel->setPos(mainx + mainwidth/4, mainy);
    }
    else if (C.contains(A))
    {
        Cel->setPos(mainx - mainshift, mainy);
        Ael->setRect(0, 0, mainwidth/1.7, mainwidth/1.7);
        Ael->setPos(Cel->pos().x() + mainwidth/4, Cel->pos().y() + mainwidth/4);
        Bel->setPos(mainx + mainwidth/4, mainy);
    }
    else if (B.contains(C))
    {
        Bel->setPos(mainx - mainshift, mainy);
        Cel->setRect(0, 0, mainwidth/1.7, mainwidth/1.7);
        Cel->setPos(Bel->pos().x() + mainwidth/4, Bel->pos().y() + mainwidth/4);
        Ael->setPos(mainx + mainwidth/4, mainy);
    }
    else if (C.contains(B))
    {
        Cel->setPos(mainx - mainshift, mainy);
        Bel->setRect(0, 0, mainwidth/1.7, mainwidth/1.7);
        Bel->setPos(Cel->pos().x() + mainwidth/4, Cel->pos().y() + mainwidth/4);
        Ael->setPos(mainx + mainwidth/4, mainy);
    }

    signalForMoveText();
}

void Scene::cat8()
{
    if (C.contains(B) && B.contains(A))
    {
        Bel->setPos(mainx - mainshift, mainy);
        Ael->setRect(0, 0, mainwidth/1.7, mainwidth/1.7);
        Ael->setPos(Bel->pos().x() + mainwidth/4, Bel->pos().y() + mainwidth/4);
        Cel->setRect(0, 0, mainwidth*1.7, mainwidth*1.7);
        Cel->setPos(Bel->pos().x() - mainwidth/4, Bel->pos().y() - mainwidth/4);
    }
    else if (C.contains(A) && A.contains(B))
    {
        Ael->setPos(mainx - mainshift, mainy);
        Bel->setRect(0, 0, mainwidth/1.7, mainwidth/1.7);
        Bel->setPos(Ael->pos().x() + mainwidth/4, Ael->pos().y() + mainwidth/4);
        Cel->setRect(0, 0, mainwidth*1.7, mainwidth*1.7);
        Cel->setPos(Ael->pos().x() - mainwidth/4, Ael->pos().y() - mainwidth/4);
    }
    else if (B.contains(A) && A.contains(C))
    {
        Ael->setPos(mainx - mainshift, mainy);
        Cel->setRect(0, 0, mainwidth/1.7, mainwidth/1.7);
        Cel->setPos(Ael->pos().x() + mainwidth/4, Ael->pos().y() + mainwidth/4);
        Bel->setRect(0, 0, mainwidth*1.7, mainwidth*1.7);
        Bel->setPos(Ael->pos().x() - mainwidth/4, Ael->pos().y() - mainwidth/4);
    }
    else if (B.contains(C) && C.contains(A))
    {
        Cel->setPos(mainx - mainshift, mainy);
        Ael->setRect(0, 0, mainwidth/1.7, mainwidth/1.7);
        Ael->setPos(Cel->pos().x() + mainwidth/4, Cel->pos().y() + mainwidth/4);
        Bel->setRect(0, 0, mainwidth*1.7, mainwidth*1.7);
        Bel->setPos(Cel->pos().x() - mainwidth/4, Cel->pos().y() - mainwidth/4);
    }
    else if (A.contains(B) && B.contains(C))
    {
        Bel->setPos(mainx - mainshift, mainy);
        Cel->setRect(0, 0, mainwidth/1.7, mainwidth/1.7);
        Cel->setPos(Bel->pos().x() + mainwidth/4, Bel->pos().y() + mainwidth/4);
        Ael->setRect(0, 0, mainwidth*1.7, mainwidth*1.7);
        Ael->setPos(Bel->pos().x() - mainwidth/4, Bel->pos().y() - mainwidth/4);
    }
    else if (A.contains(C) && C.contains(B))
    {
        Cel->setPos(mainx - mainshift, mainy);
        Bel->setRect(0, 0, mainwidth/1.7, mainwidth/1.7);
        Bel->setPos(Cel->pos().x() + mainwidth/4, Cel->pos().y() + mainwidth/4);
        Ael->setRect(0, 0, mainwidth*1.7, mainwidth*1.7);
        Ael->setPos(Cel->pos().x() - mainwidth/4, Cel->pos().y() - mainwidth/4);
    }

    signalForMoveText();
}

void Scene::cat9()
{
    if (C.contains(A))
    {
        Cel->setRect(0, 0, mainwidth*2, mainwidth*2);
        Cel->setPos(mainx - mainwidth/2, mainy - mainwidth/2);
        Ael->setRect(0, 0, mainwidth/1.7, mainwidth/1.7);
        Ael->setPos(Cel->pos().x() + mainwidth/4, Cel->pos().y() + mainwidth/2);
        Bel->setRect(0, 0, mainwidth/1.7, mainwidth/1.7);
        Bel->setPos(Cel->pos().x() + mainwidth, Cel->pos().y() + mainwidth/2);
    }
    else if (A.contains(C))
    {
        Ael->setRect(0, 0, mainwidth*2, mainwidth*2);
        Ael->setPos(mainx - mainwidth/2, mainy - mainwidth/2);
        Cel->setRect(0, 0, mainwidth/1.7, mainwidth/1.7);
        Cel->setPos(Ael->pos().x() + mainwidth/4, Ael->pos().y() + mainwidth/2);
        Bel->setRect(0, 0, mainwidth/1.7, mainwidth/1.7);
        Bel->setPos(Ael->pos().x() + mainwidth, Ael->pos().y() + mainwidth/2);
    }
    else if (B.contains(C))
    {
        Bel->setRect(0, 0, mainwidth*2, mainwidth*2);
        Bel->setPos(mainx - mainwidth/2, mainy - mainwidth/2);
        Cel->setRect(0, 0, mainwidth/1.7, mainwidth/1.7);
        Cel->setPos(Bel->pos().x() + mainwidth/4, Bel->pos().y() + mainwidth/2);
        Ael->setRect(0, 0, mainwidth/1.7, mainwidth/1.7);
        Ael->setPos(Bel->pos().x() + mainwidth, Bel->pos().y() + mainwidth/2);
    }

    signalForMoveText();
}

void Scene::cat10()
{
    if (C.contains(A))
    {
        Cel->setRect(0, 0, mainwidth*2, mainwidth*2);
        Cel->setPos(mainx - mainwidth/2, mainy - mainwidth/2);
        Ael->setRect(0, 0, mainwidth/1.7, mainwidth/1.7);
        Ael->setPos(Cel->pos().x() + mainwidth/2, Cel->pos().y() + mainwidth/2);
        Bel->setRect(0, 0, mainwidth/1.7, mainwidth/1.7);
        Bel->setPos(Cel->pos().x() + mainwidth, Cel->pos().y() + mainwidth/2);
    }
    else if (A.contains(C))
    {
        Ael->setRect(0, 0, mainwidth*2, mainwidth*2);
        Ael->setPos(mainx - mainwidth/2, mainy - mainwidth/2);
        Cel->setRect(0, 0, mainwidth/1.7, mainwidth/1.7);
        Cel->setPos(Ael->pos().x() + mainwidth/2, Ael->pos().y() + mainwidth/2);
        Bel->setRect(0, 0, mainwidth/1.7, mainwidth/1.7);
        Bel->setPos(Ael->pos().x() + mainwidth, Ael->pos().y() + mainwidth/2);
    }
    else if (B.contains(C))
    {
        Bel->setRect(0, 0, mainwidth*2, mainwidth*2);
        Bel->setPos(mainx - mainwidth/2, mainy - mainwidth/2);
        Cel->setRect(0, 0, mainwidth/1.7, mainwidth/1.7);
        Cel->setPos(Bel->pos().x() + mainwidth/2, Bel->pos().y() + mainwidth/2);
        Ael->setRect(0, 0, mainwidth/1.7, mainwidth/1.7);
        Ael->setPos(Bel->pos().x() + mainwidth, Bel->pos().y() + mainwidth/2);
    }

    signalForMoveText();
}

void Scene::cat12()
{
    if (A == B)
    {
        Ael->setPos(mainx - mainshift*1.5, mainy);
        Bel->setPos(mainx - mainshift*1.5, mainy);
        Cel->setPos(mainx + mainshift*1.5, mainy);
    }
    else if (A == C)
    {
        Ael->setPos(mainx - mainshift*1.5, mainy);
        Cel->setPos(mainx - mainshift*1.5, mainy);
        Bel->setPos(mainx + mainshift*1.5, mainy);
    }
    else if (C == B)
    {
        Cel->setPos(mainx - mainshift*1.5, mainy);
        Bel->setPos(mainx - mainshift*1.5, mainy);
        Ael->setPos(mainx + mainshift*1.5, mainy);
    }

    signalForMoveText();
}

void Scene::cat13()
{
    if (A == B)
    {
        Ael->setPos(mainx - mainshift, mainy);
        Bel->setPos(mainx - mainshift, mainy);
        Cel->setPos(mainx + mainshift/2, mainy);
    }
    else if (A == C)
    {
        Ael->setPos(mainx - mainshift, mainy);
        Cel->setPos(mainx - mainshift, mainy);
        Bel->setPos(mainx + mainshift/2, mainy);
    }
    else if (C == B)
    {
        Cel->setPos(mainx - mainshift, mainy);
        Bel->setPos(mainx - mainshift, mainy);
        Ael->setPos(mainx + mainshift/2, mainy);
    }

    signalForMoveText();
}

void Scene::cat14()
{
    if (A == B)
    {
        Cel->setRect(0, 0, mainwidth*2, mainwidth*2);
        Cel->setPos(mainx - mainwidth/2, mainy - mainwidth/2);
        Ael->setPos(mainx - mainshift/2, mainy);
        Bel->setPos(mainx - mainshift/2, mainy);
    }
    else if (A == C)
    {
        Bel->setRect(0, 0, mainwidth*2, mainwidth*2);
        Bel->setPos(mainx - mainwidth/2, mainy - mainwidth/2);
        Ael->setPos(mainx - mainshift/2, mainy);
        Cel->setPos(mainx - mainshift/2, mainy);
    }
    else if (C == B)
    {
        Ael->setRect(0, 0, mainwidth*2, mainwidth*2);
        Ael->setPos(mainx - mainwidth/2, mainy - mainwidth/2);
        Bel->setPos(mainx - mainshift/2, mainy);
        Cel->setPos(mainx - mainshift/2, mainy);
    }

    signalForMoveText();
}

void Scene::cat15()
{
    Ael->setPos(mainx, mainy);
    Bel->setPos(mainx, mainy);
    Cel->setPos(mainx, mainy);

    signalForMoveText();
}

void Scene::cat16()
{
    if (A == B)
    {
        Ael->setRect(0, 0, mainwidth*2, mainwidth*2);
        Ael->setPos(mainx - mainwidth/2, mainy - mainwidth/2);
        Bel->setRect(0, 0, mainwidth*2, mainwidth*2);
        Bel->setPos(mainx - mainwidth/2, mainy - mainwidth/2);
        Cel->setPos(mainx - mainshift/2, mainy);
    }
    else if (A == C)
    {
        Ael->setRect(0, 0, mainwidth*2, mainwidth*2);
        Ael->setPos(mainx - mainwidth/2, mainy - mainwidth/2);
        Cel->setRect(0, 0, mainwidth*2, mainwidth*2);
        Cel->setPos(mainx - mainwidth/2, mainy - mainwidth/2);
        Bel->setPos(mainx - mainshift/2, mainy);
    }
    else if (C == B)
    {
        Cel->setRect(0, 0, mainwidth*2, mainwidth*2);
        Cel->setPos(mainx - mainwidth/2, mainy - mainwidth/2);
        Bel->setRect(0, 0, mainwidth*2, mainwidth*2);
        Bel->setPos(mainx - mainwidth/2, mainy - mainwidth/2);
        Ael->setPos(mainx - mainshift/2, mainy);
    }

    signalForMoveText();
}

void Scene::colorize()
{
    fp->fillIntersects();
    updateText();
}
