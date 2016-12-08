#ifndef WETMAP_H
#define WETMAP_H

#include <QGraphicsItem>
#include <QPainter>
#include <QVector>
#include <QPointF>
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
        this->m_waterVelocitiesX = obj.m_waterVelocitiesX;
        this->m_waterVelocitiesY = obj.m_waterVelocitiesY;
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
    QPointF GetVelocity(int x, int y);

    QRectF boundingRect() const {
        return QRectF(0, 0, m_width, m_height);
    }

    QPainterPath shape () const {
        QPainterPath path;
        path.addRect(boundingRect());
        return path;
    }

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                     QWidget *widget);
    void Clear() {
        prepareGeometryChange();

        int i;
        for (int y = 0; y < m_height; y++)
            for (int x = 0; x < m_width; x++) {
                i = x + y * m_width;
                this->m_wetMap[i] = 0;
                this->m_waterVelocitiesX[i] = 0;
                this->m_waterVelocitiesY[i] = 0;
            }

        this->update(this->boundingRect());
    }

private:
    uchar* m_wetMap;
    float* m_waterVelocitiesX;
    float* m_waterVelocitiesY;
    int m_width;
    int m_height;
};

#endif // WETMAP_H
