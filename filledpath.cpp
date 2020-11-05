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

