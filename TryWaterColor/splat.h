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

double get_random(qreal min, qreal max);

class Splat : public QGraphicsItem
{
public:
    enum SplatState {
        Alive,
        Dead
    };

    Splat(QPointF offset, int width, QColor splatColor);
    Splat(QPointF offset, QPointF velocityBias, int width, int life,
          qreal roughness, qreal flow, qreal radialSpeed, QColor splatColor);
    Splat(const Splat &obj);
    Splat &operator =(const Splat &obj);

    int UpdateShape(WetMap *wetMap);
    void OptimizeShape();

    QRectF boundingRect() const {
        return m_vertices.boundingRect();
    }

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                     QWidget *widget) {
        QColor current;
        current = m_initColor;
        qreal size = (qreal) m_initSize / CalcSize();
        qreal multip = size >= 1.f ? 255 : size * 255;
        current.setAlpha(multip);
        painter->setBrush(current);
        painter->setPen(current);
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
