#include "wet_map.h"

WetMap::WetMap(int width, int height) : m_width(width), m_height(height)
{
    this->m_wetMap = new char[m_width * m_height];
}

void WetMap::Update()
{
    int i;
    char w;
    for (int y = 0; y < m_height; y++)
        for (int x = 0; x < m_width; x++) {
            i = x + y * m_width;
            w = m_wetMap[i];
            if (w > 0)
                m_wetMap[i]--;
        }
}

void WetMap::Fill(int* xs, int* ys, int xOffset, int yOffset)
{
    int length = sizeof xs / sizeof xs[0];
    for (int i = 0; i < length; i++) {
        int x = xs[i] + xOffset;
        int y = ys[i] + yOffset;
        if (x < 0 || m_width <= x || y < 0 || m_height <= y)
            continue;
        int pixIndex = x + y * m_width;
        m_wetMap[pixIndex] = 255;
    }
}

char WetMap::GetWater(int x, int y)
{
    if (x < 0 || m_width <= x || y < 0 || m_height <= y)
                    return 0;
    int pixelIndex = x + y * m_width;
    return m_wetMap[pixelIndex];
}
