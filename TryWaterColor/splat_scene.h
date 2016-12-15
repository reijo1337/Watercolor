#ifndef SPLATSCENE_H
#define SPLATSCENE_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsEllipseItem>
#include <QTimer>
#include <QPixmap>
#include <QMutex>
#include <QTime>
#include "splat.h"
#include "wet_map.h"
#include "watercolor_types.h"
#include "strategy/splat_generator_strategy.h"

class SplatGeneratorStrategy;

// TODO: Настройки кисти, полупрозрачность, смешание, счетчики производительности
// подложка текстуры бумаги.
// Квадратичное дерево для оптимизации
class SplatScene : public QGraphicsScene
{
    Q_OBJECT
public slots:
    void update();
    void updateBrushWidth(int width);
public:
    enum GenerateStrategy {
        Simple,
        WetOnDry,
        Cruncy,
        WetOnWet,
        Blobby
    };
    SplatScene();
    ~SplatScene()
    {
        delete m_cursor;
        delete m_active;
        delete m_fixed;
        delete timer;
    }

    void disableCursor();
    void setWetMap(WetMap &wetMap);
    void pushBackSplat(Splat *splatToPush);
    void fillWetMap(WaterRegion *placeForWetting, QPointF pos);

    QColor getSplatColor();
    void setSplatColor(QColor color);

    void setBrushWidth(int width);
    int getBrushWitdh();

    void setGenerateStrategy(int id);
    void VisualWet(bool wha);
    void ClearAll();

    void RewetSplats(WaterRegion *m_water, QPointF pos);
protected:
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event);
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
private:
    QPointF last_pos;
    QGraphicsEllipseItem *m_cursor;
    QList<Splat*> *m_active;
    QList<Splat*> *m_fixed;
    QList<Splat*> *m_dried;
    WetMap *m_wetMap;
    QTimer *timer;

    QTime m_startTime;

    SplatGeneratorStrategy *generator;
    QColor m_splatColor;
    int m_brushWidth;
    int optimizeIfNull;
};


#endif // SPLATSCENE_H
