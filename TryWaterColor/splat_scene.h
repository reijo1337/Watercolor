#ifndef SPLATSCENE_H
#define SPLATSCENE_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsEllipseItem>

class SplatScene : public QGraphicsScene
{
    Q_OBJECT
public:
    SplatScene();
    void disableCursor();
protected:
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event);
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
private:
    QPointF last_pos;
    QGraphicsEllipseItem *m_cursor;
};

#endif // SPLATSCENE_H
