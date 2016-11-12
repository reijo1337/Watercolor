#ifndef SPLAT_H
#define SPLAT_H

#include <QPointF>
#include <QList>
#include <QPolygonF>
#include <QColor>
#include "wet_map.h"

class Splat
{
public:
    Splat(QPointF offset, QPointF velocityBias, int width, int life, qreal roughness, qreal flow, qreal radialSpeed);
    void UpdateShape(WetMap wetMap);
    qreal CalcSize();
private:
    const float alpha = 0.33f;

    QPolygonF m_vertices;
    QList<QPointF> m_velocities;
    int m_life;
    qreal m_roughness;
    qreal m_flow;
    QPointF m_motionBias;

    qreal m_startTime;

    qreal m_initSize;
    QColor m_initColor;
};

#endif // SPLAT_H
