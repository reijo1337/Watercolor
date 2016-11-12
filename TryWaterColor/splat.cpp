#include "splat.h"

Splat::Splat()
{
    initColor.setRgb(255, 255, 255);
}

void Splat::UpdateShape(WetMap wetMap)
{
    if (life <= 0)
        return;
    life--;

    for (int i = 0; i < vertices.length(); i++) {
        QPointF x = vertices[i];
        QPointF v = velocities[i];
        QPointF d = (1.f - alpha) * motionBias +
                alpha / (1.f + static_cast <qreal> (rand()) / ( static_cast <qreal> (RAND_MAX/(roughness)))) * v;
        qreal ran = -roughness + static_cast <qreal> (rand()) / ( static_cast <qreal> (RAND_MAX/(2*roughness)));
        QPointF x1 = x + flow * d + QPointF(ran, ran);
        int wet = wetMap.GetWater((int)x1.x(), (int)x1.y()); // Считываение количества жидкости

        if (wet > 0)
            vertices[i] = x1;
    }
}
