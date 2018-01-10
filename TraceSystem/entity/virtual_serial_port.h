#ifndef VIRTUAL_SERIAL_PORT_H
#define VIRTUAL_SERIAL_PORT_H

#include <QObject>
#include <QMutex>
#include <QBasicTimer>
#include <QTimerEvent>
#include "types/trace_point_item.h"
#include <QList>
#include <QByteArray>

class Virtual_Serial_Port : public QObject
{
    Q_OBJECT
public:
    explicit Virtual_Serial_Port(QObject *parent = 0);
    ~Virtual_Serial_Port();
    void read(char* data, quint64 maxSize);
    QByteArray readAll();
    quint64 bytesAvailable() { return currentBuffer.length();}
    QList<trace_point_info*> list_InfoAboutPoints;  //список - информация о точках из файла

    int TimeOut = 0;
    void start();
    void stop();

private:
    quint32 time = 0;
    QString currentBuffer = "";
    QMutex buffMtx;
    QBasicTimer timer;

signals:
    void readyRead();

public slots:

    // QObject interface
protected:
    void timerEvent(QTimerEvent *e);
};

#endif // VIRTUAL_SERIAL_PORT_H
