#include "splat_scene.h"
#include <QVector2D>
#include <omp.h>

// This method updates all splats and wet map
void SplatScene::update()
{
    int checkSplat;

    foreach (Splat* splat, *m_active) {
        checkSplat = splat->UpdateShape(m_wetMap);

        if (checkSplat == Splat::Fixed)
        {
            m_fixed->push_back(splat);
            m_active->removeOne(splat);
        }
    }

    foreach (Splat* splat, *m_fixed) {
        checkSplat = splat->UpdateShape(m_wetMap);

        if (checkSplat == Splat::Dried)
        {
            m_dried->push_back(splat);
            m_fixed->removeOne(splat);
        }
    }

    m_wetMap->UpdateMap();
}

void SplatScene::updateBrushWidth(int width)
{
    m_brushWidth = width;
    optimizeIfNull = 3;
    this->removeItem(m_cursor);
    delete m_cursor;
    m_cursor = new QGraphicsEllipseItem(0, 0, m_brushWidth, m_brushWidth);
    this->addItem(m_cursor);
    m_cursor->hide();
}

SplatScene::SplatScene() : m_splatColor(QColor(Qt::red)), m_brushWidth(45)
{
    QPixmap background;
    background.load(":/samples/back1");
    QBrush backBrush;
    backBrush.setTexture(background);
    this->setBackgroundBrush(backBrush);
    m_cursor = new QGraphicsEllipseItem(0,0,m_brushWidth, m_brushWidth);
    m_cursor->hide();
    this->addItem(m_cursor);
    m_active = new QList<Splat*>();
    m_fixed = new QList<Splat*>();
    m_dried = new QList<Splat*>();
    m_startTime = QTime::currentTime();
    timer = new QTimer();
    timer->setInterval(33);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));

    generator = new GenSimpleBrushStrategy();
}

void SplatScene::disableCursor()
{
    if (m_cursor->isVisible())
        m_cursor->hide();
}

void SplatScene::setWetMap(WetMap &wetMap)
{
    m_wetMap = new WetMap(wetMap);
    this->addItem(m_wetMap);
    m_wetMap->hide();
}

void SplatScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    last_pos = event->scenePos();
    generator->Generate(this, event);
    if (!timer->isActive())
        timer->start();
}

void SplatScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    generator->Generate(this, event);
}

void SplatScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (!m_cursor->isVisible())
        m_cursor->show();
    m_cursor->setPos(event->scenePos().x() - m_brushWidth / 2, event->scenePos().y() - m_brushWidth / 2);

    QVector2D *m_len = new QVector2D(last_pos - event->scenePos());
    if (m_len->length() > m_brushWidth * 0.1) {
        last_pos = event->scenePos();
        generator->Generate(this, event);
    }
    this->removeItem(m_cursor);
    this->addItem(m_cursor);
}

void SplatScene::pushBackSplat(Splat *splatToPush)
{
    m_active->push_back(splatToPush);
}

void SplatScene::fillWetMap(WaterRegion *placeForWetting, QPointF pos)
{
    m_wetMap->Fill(placeForWetting, pos);
}

QColor SplatScene::getSplatColor()
{
    return m_splatColor;
}

void SplatScene::setSplatColor(QColor color)
{
    m_splatColor = color;
}

int SplatScene::getBrushWitdh()
{
    return m_brushWidth;
}

void SplatScene::setGenerateStrategy(int id)
{
    delete generator;
    switch (id) {
    case Simple:
        generator = new GenSimpleBrushStrategy();
        break;
    case WetOnDry:
        generator = new GenWetOnDryBrush();
    case Cruncy:
        generator = new GenCruncyBrush();
    case WetOnWet:
        generator = new GenWetOnWetBrush();
    case Blobby:
        generator = new GenBlobbyBrush();
    default:
        break;
    }
}

void SplatScene::VisualWet(bool wha)
{
    if (wha)
        m_wetMap->show();
    else
        m_wetMap->hide();
}

void SplatScene::ClearAll()
{
    timer->stop();
    foreach (Splat* splat, *m_active) {
        this->removeItem(splat);
    }
    foreach (Splat* splat, *m_fixed) {
        this->removeItem(splat);
    }
    foreach (Splat* splat, *m_dried) {
        this->removeItem(splat);
    }

    m_active->clear();
    m_fixed->clear();
    m_dried->clear();
    m_wetMap->Clear();
}

void SplatScene::RewetSplats(WaterRegion *m_water, QPointF pos)
{
    QList<Splat*> buf = *m_fixed;
    Splat* bufSplt;

    //#pragma omp parallel for
    for (int i = 0; i < buf.length(); i++) {
        bufSplt = buf.at(i);
        if (bufSplt->RewetShape(m_water, m_wetMap, pos) == Splat::Flowing) {
            m_active->push_back(bufSplt);
            m_fixed->removeOne(bufSplt);
        }
    }
    qDebug() << m_fixed->length() << endl;
}
