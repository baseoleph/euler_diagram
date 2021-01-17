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

#include "filledpath.h"

#include "QDebug"

FilledPath::FilledPath(int width, int height, QObject *parent):
    QObject(parent), QGraphicsItem()
{
    this->width = width;
    this->height = height;
}

FilledPath::~FilledPath()
{
}

void FilledPath::updateBoundingRect(int width, int height)
{
    this->width = width;
    this->height = height;
    update();
}

void FilledPath::fillIntersects()
{
   is_fill = true;
   update();
}

void FilledPath::unFillIntersects()
{
    path.clear();
    is_fill = false;
    update();
}

QRectF FilledPath::boundingRect() const
{
    return QRectF(0, 0, 3000, 3000);
}

void FilledPath::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->setBrush(QBrush(QColor("#F5CE6E")));
    painter->setPen(Qt::NoPen);

    if (is_fill)
    {
        painter->drawPath(path);
    }
}

