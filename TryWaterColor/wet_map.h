#ifndef WETMAP_H
#define WETMAP_H


class WetMap
{
public:
    WetMap(int width, int height);
    void Update();
    void Fill(int *xs, int* ys, int xOffset, int yOffset);
    char GetWater(int x, int y);
private:
    char* m_wetMap;
    int m_width;
    int m_height;
};

#endif // WETMAP_H
