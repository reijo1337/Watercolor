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
        Flowing,
        Fixed,
        Dried
    };

    Splat(QPointF offset, int width, QColor splatColor);
    Splat(QPointF offset, QPointF velocityBias, int width, int life,
          qreal roughness, qreal flow, qreal radialSpeed, QColor splatColor);
    Splat(const Splat &obj);
    Splat &operator =(const Splat &obj);

    int UpdateShape(WetMap *wetMap);

    QRectF boundingRect() const {
        return m_vertices.boundingRect();
    }

    QColor getColor() {
        QColor current;
        current = m_initColor;
        qreal multiply = m_initSize / CalcSize();
        if (multiply < 0.f || multiply > 1.f)
            multiply = 1;

        current.setAlpha(current.alpha() * multiply);
        return current;
    }

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                     QWidget *widget) {
        painter->setBrush(getColor());
        painter->setPen(Qt::PenStyle::NoPen);
        painter->drawPath(this->shape());
    }

    QPainterPath shape () const {
        QPainterPath path;

        int len = m_vertices.length();
        path = *(new QPainterPath(m_vertices[0]));

        for (int i = 0; i < len-2; i+=2) {
            path.quadTo(m_vertices[i+1], m_vertices[i+2]);
        }

        path.quadTo(m_vertices[len-1], m_vertices[0]);

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

    QBrush brush;

    int m_fix;
};

#endif // SPLAT_H
