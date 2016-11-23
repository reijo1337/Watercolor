#include "splat_scene.h"
#include <QVector2D>

// This method updates all splats and wet map
void SplatScene::update()
{
    m_threadLock.lock(); {
        if (m_nWetMapUpdateWorkers > 0)
        {
            m_threadLock.unlock();
            return;
        }
    } m_threadLock.unlock();

    m_locked->clear();
    foreach (Splat* splat, *m_active) {
        if (splat->startTime() < m_startTime) {
            delete splat;
        } else {
            m_locked->push_back(splat);
        }
    }

    m_active->swap(*m_locked);

    foreach (Splat* splat, *m_active) {
        splat->UpdateShape(m_wetMap);
    }

    m_threadLock.lock(); {
        m_nWetMapUpdateWorkers++;
        m_wetMap->UpdateMap();
        WetMapUpdater *dryer = new WetMapUpdater(this);
        QThreadPool::globalInstance()->start(dryer);
    } m_threadLock.unlock();
}

SplatScene::SplatScene()
{
    m_cursor = new QGraphicsEllipseItem(0,0,60,60);
    m_cursor->hide();
    this->addItem(m_cursor);
    m_active = new QList<Splat*>();
    m_locked = new QList<Splat*>();
    m_startTime = QTime::currentTime();
    timer = new QTimer();
    timer->setInterval(50);
    m_nWetMapUpdateWorkers = 0;
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
}

// Slot for disabling cursor when its outside
void SplatScene::disableCursor()
{
    if (m_cursor->isVisible())
        m_cursor->hide();
}

void SplatScene::setWetMap(WetMap &wetMap)
{
    m_wetMap = new WetMap(wetMap);
    this->addItem(m_wetMap);
   // m_wetMap->hide();
    m_wetMap->FillAll();
}

void SplatScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    last_pos = event->scenePos();
    Splat *newsplat = new Splat(event->scenePos(), 60);
    this->addItem(newsplat);
    m_active->push_back(newsplat);
    if (!timer->isActive())
        timer->start();
}

void SplatScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    Splat *newsplat = new Splat(event->scenePos(), 60);
    this->addItem(newsplat);
    m_active->push_back(newsplat);
}

void SplatScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (!m_cursor->isVisible())
        m_cursor->show();
    m_cursor->setPos(event->scenePos().x() - 30, event->scenePos().y() - 30);

    if (event->buttons() == Qt::LeftButton) {
        QVector2D *m_len = new QVector2D(last_pos - event->scenePos());
        if (m_len->length() > 3) {
            last_pos = event->scenePos();
            Splat *newsplat = new Splat(event->scenePos(), 60);
            this->addItem(newsplat);
            m_active->push_back(newsplat);
        }
    }
    this->removeItem(m_cursor);
    this->addItem(m_cursor);
}
