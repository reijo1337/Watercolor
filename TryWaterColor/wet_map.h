#ifndef WETMAP_H
#define WETMAP_H

#include <QGraphicsItem>
#include <QPainter>
#include <QMutex>
#include "watercolor_types.h"

class WetMap : public QGraphicsItem
{
public:
    WetMap(int width, int height);
    WetMap(const WetMap &obj)
    {
        m_width = obj.m_width;
        m_height = obj.m_height;
        this->m_wetMap = new unsigned char[obj.m_width * obj.m_height];
    }
    ~WetMap() {
        delete[] m_wetMap;
    }

    void UpdateMap();
    void Fill(WaterRegion *wetPlace, QPointF pos);
    void FillAll() {
        int i;
        for (int y = 0; y < m_height; y++)
            for (int x = 0; x < m_width; x++) {
                i = x + y * m_width;
                this->m_wetMap[i] = 255;
            }
    }

    char GetWater(int x, int y);

    QRectF boundingRect() const {
        return QRectF( 0, 0,
                      m_width, m_height);
    }

    QPainterPath shape () const {
        QPainterPath path;
        path.addRect(boundingRect());
        return path;
    }

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                     QWidget *widget);
private:
    uchar* m_wetMap;
    int m_width;
    int m_height;
    QMutex m_threadLock;
};

#endif // WETMAP_H
