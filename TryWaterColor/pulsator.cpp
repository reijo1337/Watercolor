#include "pulsator.h"

void Pulsator::ImmaFirinMahLazer()
{
    emit ShoopDaWoop();
}

Pulsator::Pulsator(int pulseTime, QObject *parent) : QObject(parent)
{
    m_timeBeforePulse = new QTimer();
    m_timeBeforePulse->setInterval(pulseTime);
    connect(m_timeBeforePulse, SIGNAL(timeout()),
            this, SLOT(ImmaFirinMahLazer()));
}

// tuk-tuk-tuk
void Pulsator::StartHeartbeat()
{
    m_timeBeforePulse->start();
}

// ---------------
void Pulsator::StopHeartbeat()
{
    m_timeBeforePulse->stop();
}
