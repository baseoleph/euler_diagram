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

    void colorize();
    void setCircles(QSet<int> A, QSet<int> B, QSet<int> C, int categ);
    void putOneRelatOther(QGraphicsEllipseItem *one, const QGraphicsEllipseItem *oth,
                          QSet<int> set_one, const QSet<int> set_oth);
    QGraphicsEllipseItem *Ael;
    QGraphicsEllipseItem *Bel;
    QGraphicsEllipseItem *Cel;

    FilledPath *fp;
signals:
    void signalForMoveText();

private:

    void updateText();
    int categ;
    int cell;
    int mainwidth;
    QGraphicsTextItem *At;
    QGraphicsTextItem *Bt;
    QGraphicsTextItem *Ct;
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

