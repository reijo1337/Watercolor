#include "wet_map.h"
#include <omp.h>

#include <iostream>

WetMap::WetMap(int width, int height) : m_width(width), m_height(height)
{
    this->m_wetMap = new unsigned char[width * height];
    this->m_waterVelocities = *(new QVector<QPointF>(width * height));
}

void WetMap::UpdateMap()
{
    int i;
    uchar w;
    prepareGeometryChange();
//#pragma omp parallel num_threads(3)
{
    //#pragma omp for
    for (int y = 0; y < m_height; y++)
        for (int x = 0; x < m_width; x++) {
            i = x + y * m_width;
            w = m_wetMap[i];
            if (w > 0) {
                m_wetMap[i]--;
            } else {
//                m_waterVelocities[i].setX(0);
//                m_waterVelocities[i].setY(0);
            }
        }
}
    this->update(this->boundingRect());
}

void WetMap::Fill(WaterRegion *wetPlace, QPointF pos)
{
    prepareGeometryChange();
    QPointF p;
    QPointF pr;
    foreach (QPoint wetDot, *wetPlace) {
        int x = wetDot.x() + pos.x();
        int y = wetDot.y() + pos.y();
        if (x < 0 || m_width <= x || y < 0 || m_height <= y)
            continue;

        p.setX(2.f * (qreal) wetDot.x() / wetDot.manhattanLength());
        p.setX(2.f * (qreal) wetDot.y() / wetDot.manhattanLength());
        int pixIndex = x + y * m_width;
        m_wetMap[pixIndex] = 255;

        pr = m_waterVelocities[pixIndex] + p;

        m_waterVelocities[pixIndex].setX(2.f * pr.x() / pr.manhattanLength());
        m_waterVelocities[pixIndex].setY(2.f * pr.y() / pr.manhattanLength());
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

void WetMap::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    int i;
    uchar w;
    QImage image(m_width, m_height, QImage::Format_ARGB32_Premultiplied);
    painter->setBackground(Qt::white);

//    #pragma omp parallel num_threads(1)
    {
//        #pragma omp for
        for (int y = 0; y < m_height; y++)
            for (int x = 0; x < m_width; x++) {
                i = x + y * m_width;
                w = this->m_wetMap[i];
                image.setPixelColor(x, y, QColor(0, 0, 255, (int) w));
            }
    }
    painter->drawImage(0, 0, image);
}

