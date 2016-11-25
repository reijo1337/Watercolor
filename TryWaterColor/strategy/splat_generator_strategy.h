#ifndef SPLATGENERATORSTRATEGY_H
#define SPLATGENERATORSTRATEGY_H

#include <QList>
#include <QPoint>
#include <QGraphicsSceneMouseEvent>
#include <splat.h>
#include <splat_scene.h>
#include "watercolor_types.h"

class SplatScene;

class SplatGeneratorStrategy
{
public:
    virtual ~SplatGeneratorStrategy() {}
    virtual void Generate(SplatScene *scene, QGraphicsSceneMouseEvent *event) = 0;
protected:
    void CreateSimpleBrush (int width);
    WaterRegion *m_water;
};

class GenSimpleBrushStrategy : public SplatGeneratorStrategy
{
public:
    void Generate(SplatScene *scene, QGraphicsSceneMouseEvent *event);
};

class GenWetOnDryBrush : public SplatGeneratorStrategy
{
public:
    void Generate(SplatScene *scene, QGraphicsSceneMouseEvent *event);
};

class GenCruncyBrush : public SplatGeneratorStrategy
{
public:
    void Generate(SplatScene *scene, QGraphicsSceneMouseEvent *event);
};

#endif // SPLATGENERATORSTRATEGY_H
