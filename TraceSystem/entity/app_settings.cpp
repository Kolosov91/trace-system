#include "app_settings.h"

App_Settings::App_Settings(QObject *parent) : QObject(parent)
{

}

App_Settings::~App_Settings()
{

}

void App_Settings::load()
{
    QSettings* rdOpt = new QSettings(this->NameFileSettings, QSettings::IniFormat);
    rdOpt->beginGroup("/Settings");
    this->nameComPort = rdOpt->value("/currentNameCOM", this->VirtPortConst).toString();
    this->currentBaudRateCOM = (QSerialPort::BaudRate)(rdOpt->value("/currentBaudRateCOM", QSerialPort::Baud115200).toInt());
    this->lastOpenDir = rdOpt->value("/lastOpenDir", ".").toString();
    rdOpt->endGroup();
    delete rdOpt;
}

void App_Settings::save()
{
    QSettings* wrOpt = new QSettings(this->NameFileSettings, QSettings::IniFormat);
    wrOpt->beginGroup("/Settings");
    wrOpt->setValue("/currentNameCOM" , this->nameComPort);
    wrOpt->setValue("/currentBaudRateCOM", this->currentBaudRateCOM);
    wrOpt->setValue("/lastOpenDir" , this->lastOpenDir);
    wrOpt->endGroup();
    wrOpt->sync();
    delete wrOpt;
}

