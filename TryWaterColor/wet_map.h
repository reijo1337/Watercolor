#ifndef WETMAP_H
#define WETMAP_H

#include <QGraphicsItem>
#include <QPainter>
#include <QThreadPool>
#include <QMutex>

class PainterInThread;

class WetMap : public QGraphicsItem
{
public:
    friend class PainterInThread;
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
    void Fill(int *xs, int* ys, int xOffset, int yOffset);
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

class PainterInThread : public QRunnable
{
public:
    PainterInThread(WetMap* wetMap, QPainter* painter)
    {
        wetMapForThread = wetMap;
        m_painter = painter;
    }

    void run() {
        int i;
        uchar w;
        QImage image(wetMapForThread->m_width, wetMapForThread->m_height, QImage::Format_ARGB32_Premultiplied);
        m_painter->setBackground(Qt::white);
        for (int y = 0; y < wetMapForThread->m_height; y++)
            for (int x = 0; x < wetMapForThread->m_width; x++) {
                i = x + y * wetMapForThread->m_width;
                w = this->wetMapForThread->m_wetMap[i];
                image.setPixelColor(x, y, QColor(0, 0, 255, (int) w));
            }
        m_painter->drawImage(0, 0, image);
    }
private:
    QPainter *m_painter;
    WetMap *wetMapForThread;
};

#endif // WETMAP_H
