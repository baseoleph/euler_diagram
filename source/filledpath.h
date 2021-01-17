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

#ifndef FILLEDPATH_H
#define FILLEDPATH_H

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include <QGraphicsScene>
#include <QGraphicsEllipseItem>

class FilledPath : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit FilledPath(int width = 0, int height = 0, QObject *parent = 0);
    ~FilledPath();

    QPainterPath ar;
    QPainterPath br;
    QPainterPath cr;

    QPainterPath path;

    void updateBoundingRect(int width, int height);
    void fillIntersects();
    void unFillIntersects();
protected:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:
    bool is_fill = false;
    int width;
    int height;
};


#endif // FILLEDPATH_H
