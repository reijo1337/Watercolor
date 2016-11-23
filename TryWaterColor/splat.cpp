#include "splat.h"
#include "stdlib.h"
#include <ctime>

Splat::Splat(QPointF offset, int width)
    : m_life(60), m_roughness(1.f), m_flow(1.f), m_motionBias(QPointF(0.f, 0.f))
{
    srand(time(0));
    int r = width / 2;
    int n = 25;

    qreal dt = 2.f * M_PI / n;
    QPointF p;
    for (int i = 0; i < n; i++)
    {
        p.setX(cos(i * dt));
        p.setY(sin(i * dt));
        m_vertices.push_back(QPointF(static_cast <qreal> (r * p.x()) + offset.x(),
                                     static_cast <qreal> (r * p.y()) + offset.y()));
        m_velocities.push_back(QPointF(2.f * p.x(),
                                       2.f * p.y()));
    }
    m_initColor.setRgb(255, 0, 0);
    m_initSize = CalcSize();
    m_startTime = QTime::currentTime();
}

Splat::Splat(QPointF offset, QPointF velocityBias, int width, int life, qreal roughness, qreal flow, qreal radialSpeed)
    : m_life(life), m_roughness(roughness), m_flow(flow), m_motionBias(velocityBias)
{
    srand(time(0));
    int r = width / 2;
    int n = 25;

    qreal dt = 2.f * M_PI / n;
    QPointF p;
    for (int i = 0; i < n; i++)
    {
        p.setX(cos(i * dt));
        p.setY(sin(i * dt));
        m_vertices[i].setX(static_cast <qreal> (r * p.x()) + offset.x());
        m_vertices[i].setY(static_cast <qreal> (r * p.y()) + offset.y());
        m_velocities[i].setX(radialSpeed * p.x());
        m_velocities[i].setY(radialSpeed * p.y());
    }
    m_initColor.setRgb(255, 0, 0);
    m_initSize = CalcSize();
    m_startTime = QTime::currentTime();
}

Splat::Splat(const Splat &obj)
{
    srand(time(0));
    m_vertices = obj.m_vertices;
    m_velocities = obj.m_velocities;
    m_life = obj.m_life;
    m_roughness = obj.m_roughness;
    m_flow = obj.m_flow;
    m_motionBias = obj.m_motionBias;

    m_startTime = obj.m_startTime;

    m_initSize = obj.m_initSize;
    m_initColor = obj.m_initColor;
}

Splat &Splat::operator =(const Splat &obj)
{
    Splat ret(QPoint(0,0),0);
    ret.m_vertices = obj.m_vertices;
    ret.m_velocities = obj.m_velocities;
    ret.m_life = obj.m_life;
    ret.m_roughness = obj.m_roughness;
    ret.m_flow = obj.m_flow;
    ret.m_motionBias = obj.m_motionBias;

    ret.m_startTime = obj.m_startTime;

    ret.m_initSize = obj.m_initSize;
    ret.m_initColor = obj.m_initColor;

    return ret;
}

int Splat::UpdateShape(WetMap *wetMap)
{
    if (m_life <= 0)
        return Splat::Dead;
    m_life--;
    prepareGeometryChange();
    for (int i = 0; i < m_vertices.length(); i++) {
        QPointF x = m_vertices[i];
        QPointF v = m_velocities[i];
        QPointF d = (1.f - alpha) * m_motionBias +
                alpha / (1.f + static_cast <qreal> (rand()) / ( static_cast <qreal> (RAND_MAX/(m_roughness)))) * v;
        qreal ran = -m_roughness + static_cast <qreal> (rand()) / ( static_cast <qreal> (RAND_MAX/(2*m_roughness)));
        QPointF x1 = x + m_flow * d + QPointF(ran, ran);
        uchar wet = wetMap->GetWater((int)x1.x(), (int)x1.y()); // Считываение количества жидкости

        if ((int)wet > 0)
            m_vertices[i] = x1;
    }

    this->update(this->boundingRect());
    return Splat::Alive;
}

qreal Splat::CalcSize()
{
    if (m_vertices.length() < 3)
        return 0.f;
    QPointF v0 = m_vertices[0];
    qreal v0x = v0.x();
    qreal v0y = v0.y();
    QPointF e0 = m_vertices[1] - v0;
    qreal e0x = e0.x();
    qreal e0y = e0.y();
    qreal s = 0.f;
    int length = m_vertices.length();
    for (int i = 2; i < length; i++) {
        QPointF v2 = m_vertices[i];
        qreal e1x = v2.x() - v0x;
        qreal e1y = v2.y() - v0y;
        s += e0x * e1y - e0y * e1x;
        e0x = e1x;
        e0y = e1y;
    }

    return s >= 0 ? s : -s;
}

QTime Splat::startTime()
{
    return m_startTime;
}
