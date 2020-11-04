#include "filledpath.h"

#include "QDebug"

FilledPath::FilledPath(int width, int height, QObject *parent):
    QObject(parent), QGraphicsItem()
{
    this->width = width;
    this->height = height;

    AwBC.setFillRule(Qt::WindingFill);
    BwAC.setFillRule(Qt::WindingFill);
    CwAB.setFillRule(Qt::WindingFill);
    ABwC.setFillRule(Qt::WindingFill);
    ACwB.setFillRule(Qt::WindingFill);
    BCwA.setFillRule(Qt::WindingFill);
    ABC.setFillRule(Qt::WindingFill);
}

FilledPath::~FilledPath()
{
}

void FilledPath::fillIntersects()
{
   is_fill = true;
   update();
}

void FilledPath::unFillIntersects()
{
    AwBC.clear();
    BwAC.clear();
    CwAB.clear();
    ABwC.clear();
    ACwB.clear();
    BCwA.clear();
    ABC.clear();
    is_fill = false;
    update();
}

QRectF FilledPath::boundingRect() const
{
    return QRectF(0, 0, 1000, 1000);
}

void FilledPath::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->setBrush(QBrush(QColor(Qt::darkGray)));
    painter->setPen(Qt::NoPen);

    if (is_fill)
    {
        qDebug() << ABC;
        if (not ABC.isEmpty()) painter->drawPath(ABC);
        if (not ABwC.isEmpty()) painter->drawPath(ABwC);
        if (not ACwB.isEmpty()) painter->drawPath(ACwB);
        if (not BCwA.isEmpty()) painter->drawPath(BCwA);
        if (not AwBC.isEmpty()) painter->drawPath(AwBC);
        if (not BwAC.isEmpty()) painter->drawPath(BwAC);
        if (not CwAB.isEmpty()) painter->drawPath(CwAB);
    }
}

