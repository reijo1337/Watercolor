#ifndef SPLAT_H
#define SPLAT_H

#include <QPointF>
#include <QList>
#include <QPolygonF>
#include <QColor>
#include <QGraphicsItem>
#include <QPainter>
#include <QDebug>
#include <QTime>
#include "wet_map.h"

class Splat : public QGraphicsItem
{
public:
    enum SplatState {
        Alive,
        Dead
    };

    Splat(QPointF offset, int width);
    Splat(QPointF offset, QPointF velocityBias, int width, int life,
          qreal roughness, qreal flow, qreal radialSpeed);
    Splat(const Splat &obj);
    Splat &operator =(const Splat &obj);
    int UpdateShape(WetMap *wetMap);

    QRectF boundingRect() const {
        return m_vertices.boundingRect();
    }

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                     QWidget *widget) {
        painter->setBrush(m_initColor);
        painter->setPen(m_initColor);
        painter->drawPolygon(m_vertices);
    }

    QPainterPath shape () const {
        QPainterPath path;
        path.addPolygon(m_vertices);
        return path;
    }

    qreal CalcSize();

    QTime startTime();
private:
    const float alpha = 0.33f;

    QPolygonF m_vertices;
    QList<QPointF> m_velocities;
    int m_life;
    qreal m_roughness;
    qreal m_flow;
    QPointF m_motionBias;

    QTime m_startTime;

    qreal m_initSize;
    QColor m_initColor;
};

#endif // SPLAT_H
