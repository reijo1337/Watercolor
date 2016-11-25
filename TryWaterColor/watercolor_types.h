#ifndef WATERCOLOR_TYPES_H
#define WATERCOLOR_TYPES_H

#include "pulsator.h"
#include "pulsator_singleton.h"
#include <QList>
#include <QPoint>

typedef PulsatorSingleton<Pulsator> Heart;
typedef QList<QPoint> WaterRegion;

#endif // WATERCOLOR_TYPES_H
