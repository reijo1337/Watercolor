#ifndef PULSATOR_H
#define PULSATOR_H

#include <QTimer>
#include <QObject>

class Pulsator : public QObject
{
    Q_OBJECT
public:
    explicit Pulsator(int pulseTime, QObject *parent = 0);
    void StartHeartbeat();
    void StopHeartbeat();
signals:
    void ShoopDaWoop();
public slots:
    void ImmaFirinMahLazer();
private:
    QTimer *m_timeBeforePulse;
};

#endif // PULSATOR_H
