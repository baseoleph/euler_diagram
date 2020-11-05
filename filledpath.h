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
