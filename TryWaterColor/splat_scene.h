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


// TODO: Настройки кисти, полупрозрачность, смешание, счетчики производительности
// подложка текстуры бумаги.
class SplatScene : public QGraphicsScene
{
    Q_OBJECT
public slots:
    void update();
public:
    SplatScene();
    void disableCursor();
    void setWetMap(WetMap &wetMap);
protected:
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event);
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
private:
    QPointF last_pos;
    QGraphicsEllipseItem *m_cursor;
    QList<Splat*> *m_active;
    QList<Splat*> *m_locked;
    WetMap *m_wetMap;
    QTimer *timer;

    QTime m_startTime;
};


#endif // SPLATSCENE_H
