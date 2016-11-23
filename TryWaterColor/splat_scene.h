#ifndef SPLATSCENE_H
#define SPLATSCENE_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsEllipseItem>
#include <QTimer>
#include <QPixmap>
#include <QMutex>
#include <QTime>
#include <QThreadPool>
#include <QRunnable>
#include "splat.h"
#include "wet_map.h"

class WetMapUpdater;

class SplatScene : public QGraphicsScene
{
    Q_OBJECT
public slots:
    void update();
public:
    friend class WetMapUpdater;
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

    QMutex m_threadLock;
    int m_nWetMapUpdateWorkers;

    QTime m_startTime;
};

class WetMapUpdater : public QRunnable
{
public:
    WetMapUpdater(SplatScene* scene) {
        m_scene = scene;
    }

    void run()
    {
        m_scene->m_wetMap->UpdateMap();
        m_scene->m_threadLock.lock();
        m_scene->m_nWetMapUpdateWorkers--;
        m_scene->m_threadLock.unlock();
    }
private:
    SplatScene* m_scene;
};

#endif // SPLATSCENE_H
