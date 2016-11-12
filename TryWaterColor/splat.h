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
    Splat();
    void UpdateShape(WetMap wetMap);
private:
    const float alpha = 0.33f;

    QPolygonF vertices;
    QPointF motionBias;
    QList<QPointF> velocities;
    int life;
    qreal roughness;
    float flow;

    float startTime;

    float initSize;
    QColor initColor;
};

#endif // SPLAT_H
