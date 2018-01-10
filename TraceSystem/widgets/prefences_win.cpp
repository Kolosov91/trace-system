#include "prefences_win.h"
#include "ui_prefences_win.h"
#include "entity/app_settings.h"
#include <QList>
#include <QtSerialPort/QtSerialPort>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QMessageBox>
#include <QDesktopWidget>

prefences_win::prefences_win(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::prefences_win)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::Dialog);
    this->setWindowModality(Qt::WindowModal);

    App_Settings opt;
    opt.load();

    //Добавление портов (источников данных)
    ui->comboBox_srcData->addItem(opt.VirtPortConst);
    QSerialPortInfo* serialInfo = new QSerialPortInfo();
    QList<QSerialPortInfo> listPorts = serialInfo->availablePorts();
    foreach (QSerialPortInfo port, listPorts) {
        ui->comboBox_srcData->addItem(port.portName());
    }
    //Выбор текущего
    for(int i = 0; i<ui->comboBox_srcData->count(); i++)
        if (opt.nameComPort.compare(ui->comboBox_srcData->itemText(i)) == 0)
        {
            ui->comboBox_srcData->setCurrentIndex(i);
            break;
        }
        else ui->comboBox_srcData->setCurrentIndex(-1);

    //Добавить скорости
    QList<QSerialPort::BaudRate> arrayBaudRates =
    QList<QSerialPort::BaudRate>{QSerialPort::Baud1200, QSerialPort::Baud2400, QSerialPort::Baud4800,
    QSerialPort::Baud9600, QSerialPort::Baud19200, QSerialPort::Baud38400,
    QSerialPort::Baud57600, QSerialPort::Baud115200};
    foreach (QSerialPort::BaudRate rate, arrayBaudRates) {
        ui->comboBox_baudRate->addItem(QString::number(rate), (int)rate);
    }
    //Выбрать текущую скорость
    for(int i = 0; i<ui->comboBox_baudRate->count(); i++)
        if ((int)opt.currentBaudRateCOM == (ui->comboBox_baudRate->itemData(i).toInt()))
        {
            ui->comboBox_baudRate->setCurrentIndex(i);
            break;
        }
    else ui->comboBox_baudRate->setCurrentIndex(-1);
    delete serialInfo;

    //координаты
    QDesktopWidget* desktop = QApplication::desktop();
    QRect rect_desktop = desktop->availableGeometry(this);
    this->move(QPoint(rect_desktop.width()/2 - this->width()/2, rect_desktop.height()/2 - this->height()/2));
}

prefences_win::~prefences_win()
{
    delete ui;
}

void prefences_win::on_pushButton_accept_clicked()
{
    App_Settings opt;
    //Сохраняем источник данных
    if (ui->comboBox_srcData->currentIndex() != -1)
    {
        opt.nameComPort = ui->comboBox_srcData->currentText();
        QSerialPortInfo* serialInfo = new QSerialPortInfo(opt.nameComPort);
        if (serialInfo->isBusy())
        {
            QMessageBox* msg = new  QMessageBox(this);
            msg->setText(QString("%1 - занят!").arg(opt.nameComPort));
            msg->show();
            return;
        }
    }
    else
    {
        QMessageBox* msg = new  QMessageBox(this);
        msg->setText(QString("Не выбран источник данных!"));
        msg->show();
        return;
    }
    //Сохраняем скорость
    if (ui->comboBox_baudRate->currentIndex() != -1)
    {
        opt.currentBaudRateCOM = (QSerialPort::BaudRate)(ui->comboBox_baudRate->currentData().toInt());
    }
    else
    {
        QMessageBox* msg = new  QMessageBox(this);
        msg->setText(QString("Не выбрана скорость!"));
        msg->show();
        return;
    }
    opt.save();
    this->setResult(0);
    this->accept();
    //close();
}

void prefences_win::on_pushButton_cancel_clicked()
{
    this->setResult(-1);
    this->reject();
}
