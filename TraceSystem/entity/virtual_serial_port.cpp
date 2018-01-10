#include "virtual_serial_port.h"
#include <QTime>

Virtual_Serial_Port::Virtual_Serial_Port(QObject *parent) : QObject(parent)
{
    QTime currTime = QTime::currentTime();
    qsrand(currTime.secsTo(currTime));
}

Virtual_Serial_Port::~Virtual_Serial_Port()
{

}

void Virtual_Serial_Port::read(char *data, quint64 maxSize)
{
   buffMtx.lock();
   if (!currentBuffer.isEmpty())
   {
       quint64 len = (maxSize > (quint64)currentBuffer.length()) ? maxSize : currentBuffer.length();      
       QByteArray ba = currentBuffer.toLocal8Bit();
       char *tempArr = ba.data();
       for(quint64 i=0; i<len; i++)
          data[i] =  tempArr[i];
       currentBuffer = currentBuffer.remove(0,len);
   }
   buffMtx.unlock();
}

QByteArray Virtual_Serial_Port::readAll()
{
    QByteArray ba;
    buffMtx.lock();
    if (!currentBuffer.isEmpty())
    {
        quint64 len = currentBuffer.length();
        ba = currentBuffer.toLocal8Bit();
        currentBuffer = currentBuffer.remove(0,len);
    }
    buffMtx.unlock();
    return ba;
}

void Virtual_Serial_Port::start()
{
    timer.start(TimeOut, this);
}

void Virtual_Serial_Port::stop()
{
    timer.stop();
}

#define RAND(k, n) qrand()%(n-k+1)+k  //от N до K

void Virtual_Serial_Port::timerEvent(QTimerEvent *e)
{
    if (e->timerId() == timer.timerId())
    {
        buffMtx.lock();
        int index = RAND(0, list_InfoAboutPoints.length()-1);

        QString keyPoint = list_InfoAboutPoints.at(index)->value_key.mid(1,list_InfoAboutPoints.at(index)->value_key.length()-2);

        QString value = QString("TRC*%1*%2*%3*%4\n")
                .arg(QString::number(time))
                .arg(keyPoint)
                .arg(QString::number(RAND(0, 1)))
                .arg(QString::number(RAND(0, 2500)));
        currentBuffer = currentBuffer.append(value);
        time += RAND(10, 100);
        buffMtx.unlock();
        emit readyRead();
        return;
    }
}
