#include "splat_generator_strategy.h"
#include "cmath"
#include <QVector2D>

void SplatGeneratorStrategy::CreateSimpleBrush(int width)
{
    int r = width / 2;

    if (this->m_water)
        delete m_water;

    this->m_water = new WaterRegion();
    for (int y = -r; y <= r; y++)
        for (int x = -r; x <= r; x++) {
            int sqr = x*x + y*y;
            if (sqr <= r*r)
                this->m_water->push_back(QPoint(x, y));
        }
}

void GenSimpleBrushStrategy::Generate(SplatScene *scene, QGraphicsSceneMouseEvent *event)
{
    QColor paintColor = scene->getSplatColor();
    int width = scene->getBrushWitdh();
    if (event->buttons() == Qt::LeftButton) {
        Splat *newsplat = new Splat(event->scenePos(), width, paintColor);
        scene->addItem(newsplat);
        scene->pushBackSplat(newsplat);
        this->CreateSimpleBrush(width);
        scene->fillWetMap(m_water, event->scenePos());
    }
}

void GenWetOnDryBrush::Generate(SplatScene *scene, QGraphicsSceneMouseEvent *event)
{
    QColor paintColor = scene->getSplatColor();
    int width = scene->getBrushWitdh();
    qreal radialSpeed = 2.f;
    int d = width / 2;
    int r = d / 2;
    QVector2D offset;
    if (event->buttons() == Qt::LeftButton) {
        this->CreateSimpleBrush(width);
        scene->fillWetMap(m_water, event->scenePos());

        Splat *newsplat = new Splat(event->scenePos(), width, paintColor);
        scene->addItem(newsplat);
        scene->pushBackSplat(newsplat);

        for (int i = 0; i < 6; i++) {
            qreal theta = i * M_PI / 3;
            offset.setX(r * cos(theta));
            offset.setY(r * sin(theta));

            newsplat = new Splat(event->scenePos() + offset.toPointF(),
                                 0.1f * radialSpeed * offset.normalized().toPointF(),
                                 d, 30, 0.5f * radialSpeed, 1.f, radialSpeed, paintColor);
            scene->addItem(newsplat);
            scene->pushBackSplat(newsplat);
        }
    }
}

void GenCruncyBrush::Generate(SplatScene *scene, QGraphicsSceneMouseEvent *event)
{
    QColor paintColor = scene->getSplatColor();
    int width = scene->getBrushWitdh();
    if (event->buttons() == Qt::LeftButton) {
        this->CreateSimpleBrush(width * 2);
        scene->fillWetMap(m_water, event->scenePos());

        Splat *newsplat = new Splat(event->scenePos(), QPointF(0, 0), width,
                                    15, 5, 0.25f, 2.f, paintColor);
        scene->addItem(newsplat);
        scene->pushBackSplat(newsplat);
    }
}

void GenWetOnWetBrush::Generate(SplatScene *scene, QGraphicsSceneMouseEvent *event)
{
    QColor paintColor = scene->getSplatColor();
    int width = scene->getBrushWitdh();
    int smallD = width / 2;
    int bigD = 3 * width / 2;

    if (event->buttons() == Qt::LeftButton) {
        this->CreateSimpleBrush(width);
        scene->fillWetMap(m_water, event->scenePos());

        Splat *newsplat = new Splat(event->scenePos(), QPointF(0, 0), bigD,
                                    15, 5, 1.f, 2.f, paintColor);
        scene->addItem(newsplat);
        scene->pushBackSplat(newsplat);

        newsplat = new Splat(event->scenePos(), QPointF(0, 0), smallD,
                                    15, 5, 1.f, 2.f, paintColor);
        scene->addItem(newsplat);
        scene->pushBackSplat(newsplat);
    }
}

void GenBlobbyBrush::Generate(SplatScene *scene, QGraphicsSceneMouseEvent *event)
{
    QColor paintColor = scene->getSplatColor();
    int width = scene->getBrushWitdh();
    qreal firstD = (qreal) width / 3;
    qreal lastD = (qreal) width;
    Splat *newsplat;
    if (event->buttons() == Qt::LeftButton) {
        this->CreateSimpleBrush(width);
        scene->fillWetMap(m_water, event->scenePos());
        for (int i = 0; i < 4; i++) {
            qreal size = get_random(firstD, lastD);
            QPointF pos;
            switch (i) {
            case 0:
                pos = event->scenePos() + QPointF(0, (width - size) / 2);
                break;
            case 1:
                pos = event->scenePos() + QPointF((width - size) / 2, 0);
            case 2:
                pos = event->scenePos() - QPointF(0, (width - size) / 2);
                break;
            case 3:
                pos = event->scenePos() - QPointF((width - size) / 2, 0);
            default:
                break;
            }

            newsplat = new Splat(pos, QPointF(0, 0), size,
                                 15, 5, 1.f, 2.f, paintColor);
            scene->addItem(newsplat);
            scene->pushBackSplat(newsplat);
        }
    }
}
