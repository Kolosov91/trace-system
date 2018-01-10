#ifndef APP_SETTINGS_H
#define APP_SETTINGS_H

#include <QObject>
#include <QSettings>
#include <QtSerialPort/QtSerialPort>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>

class App_Settings : public QObject
{
    Q_OBJECT
public:
    explicit App_Settings(QObject *parent = 0);
    ~App_Settings();

    void load();
    void save();

    const QString VirtPortConst = QString("Virtual Port");

    QString nameComPort;
    QSerialPort::BaudRate currentBaudRateCOM;
    QString lastOpenDir;

private:
    const QString NameFileSettings = "TracingSystemApplication";

signals:

public slots:
};

#endif // APP_SETTINGS_H
