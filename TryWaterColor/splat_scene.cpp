#include "splat_scene.h"
#include <QVector2D>

SplatScene::SplatScene()
{
    m_cursor = new QGraphicsEllipseItem(0,0,60,60);
    m_cursor->hide();
    this->addItem(m_cursor);
}

void SplatScene::disableCursor()
{
    if (m_cursor->isVisible())
        m_cursor->hide();
}

void SplatScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    last_pos = event->scenePos();
    this->addEllipse(event->scenePos().x() - 30, event->scenePos().y() - 30, 60, 60,
                     QPen(Qt::black), QBrush(Qt::black));
}

void SplatScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    this->addEllipse(event->scenePos().x() - 30, event->scenePos().y() - 30, 60, 60,
                     QPen(Qt::black), QBrush(Qt::black));
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
            this->addEllipse(event->scenePos().x() - 30, event->scenePos().y() - 30, 60, 60,
                             QPen(Qt::black), QBrush(Qt::black));
        }
    }
}
