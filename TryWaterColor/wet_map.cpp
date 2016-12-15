#include "wet_map.h"
#include <omp.h>

#include <iostream>

WetMap::WetMap(int width, int height) : m_width(width), m_height(height)
{
    this->m_wetMap = new unsigned char[width * height];
    this->m_waterVelocitiesX = new float[width * height];
    this->m_waterVelocitiesY = new float[width * height];
}

void WetMap::UpdateMap()
{
    int i;
    uchar w;
    prepareGeometryChange();

    int x, y;
    #pragma omp for /*private(x)*/
    for (y = 0; y < m_height; y++)
        for (x = 0; x < m_width; x++) {
            i = x + y * m_width;
            w = m_wetMap[i];
            if (w > 0) {
                m_wetMap[i]--;
            } else {
                m_waterVelocitiesX[i] = 0;
                m_waterVelocitiesY[i] = 0;
            }
        }


    this->update(this->boundingRect());
}

void WetMap::Fill(WaterRegion *wetPlace, QPointF pos)
{
    prepareGeometryChange();
    foreach (QPoint wetDot, *wetPlace) {
        int x = wetDot.x() + pos.x();
        int y = wetDot.y() + pos.y();
        if (x < 0 || m_width <= x || y < 0 || m_height <= y)
            continue;

        int pixIndex = x + y * m_width;
        m_wetMap[pixIndex] = 255;

        m_waterVelocitiesX[pixIndex] = 4.f * wetDot.x() / wetDot.manhattanLength();
        m_waterVelocitiesY[pixIndex] = 4.f * wetDot.y() / wetDot.manhattanLength();
    }
    this->update(this->boundingRect());
}

char WetMap::GetWater(int x, int y)
{
    if (x < 0 || m_width <= x || y < 0 || m_height <= y)
                    return 0;
    int pixelIndex = x + y * m_width;
    return m_wetMap[pixelIndex];
}

QPointF WetMap::GetVelocity(int x, int y)
{
    if (x < 0 || m_width <= x || y < 0 || m_height <= y)
                    return QPointF(0,0);
    int pixelIndex = x + y * m_width;
    return QPointF(m_waterVelocitiesX[pixelIndex], m_waterVelocitiesY[pixelIndex]);
}

void WetMap::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    int i;
    uchar w;
    QImage image(m_width, m_height, QImage::Format_ARGB32_Premultiplied);
    painter->setBackground(Qt::white);

    for (int y = 0; y < m_height; y++)
        for (int x = 0; x < m_width; x++) {
            i = x + y * m_width;
            w = this->m_wetMap[i];
            image.setPixelColor(x, y, QColor(0, 0, 255, (int) w));
        }
    painter->drawImage(0, 0, image);
}

