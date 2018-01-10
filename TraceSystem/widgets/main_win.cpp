#include "main_win.h"
#include "ui_main_win.h"

Main_Win::Main_Win(QWidget *parent) :
    Base_Win(parent),
    ui(new Ui::Main_Win)
{
    ui->setupUi(this);

    settings = new App_Settings(this);
    settings->load();

    if (settings->nameComPort.compare(settings->VirtPortConst) == 0)
    {
        ui->label_sourceData->setText(QString("Источник данных:   %1").arg(settings->VirtPortConst));
    }
    else
    {
        ui->label_sourceData->setText(QString("Источник данных:   %1").arg("COM-X"));
    }

//// Подключение и настройка виджета системных кнопок
    CONNECT_TO_widget_system_buttons(ui->widget_SystemButtons, this);
    connect(ui->pushButton_adaptate, SIGNAL(clicked()), this, SLOT(sl_onwin_click()));
    ui->widget_SystemButtons->setVisible_onwin_button(false);

//// Подключение кнопок - показать/скрыть
    treeFilesWin = new tree_files_win(this);
    connect(treeFilesWin, SIGNAL(si_hide()), ui->pushButton_treeFilesWin, SLOT(click()));
    filesViewerWin = new files_viewer_win(this);
    connect(filesViewerWin, SIGNAL(si_hide()), ui->pushButton_filesViewerWin, SLOT(click()));
    listPointWin = new list_point_win(this);
    connect(listPointWin, SIGNAL(si_hide()), ui->pushButton_listPointWin, SLOT(click()));
    terminalWin = new terminal_win(this);
    connect(terminalWin, SIGNAL(si_hide()), ui->pushButton_terminalWin, SLOT(click()));

//// Подключение кнопок
    connect(ui->pushButton_startTraceFromComPort, SIGNAL(clicked(bool)), this, SLOT(on_start_stop_clicked_virtualPort(bool)));
    connect(ui->pushButton_startTraceFromComPort, SIGNAL(clicked(bool)), this, SLOT(on_start_stop_clicked_comPort(bool)));
    connect(ui->pushButton_prefences, SIGNAL(clicked()), this, SLOT(on_pushButton_prefencesWin_clicked()));
    connect(ui->pushButton_clearTrace, SIGNAL(clicked()), this, SLOT(on_pushButton_clear_clicked()));
    connect(ui->pushButton_clearTrace, SIGNAL(clicked()), this->listPointWin, SLOT(sl_clear_list_trace_points()));
    connect(ui->pushButton_clearTrace, SIGNAL(clicked()), this->terminalWin, SLOT(sl_clear_terminal()));
    connect(ui->pushButton_viewAll, SIGNAL(clicked()), this, SLOT(on_pushButton_viewAll_clicked()));
    connect(ui->pushButton_createTracePointsList, SIGNAL(clicked()), this, SLOT(on_pushButton_tracePointList_clicked()));
   // connect(ui->pushButton_aboutApp, SIGNAL(clicked()), this, SLOT(on_pushButton_aboutApp_clicked()));

//// Соединение дочерних окон между собой
    /// Соединение "ГЛАВНОГО ОКНА" с  Остальныим Окнами
    connect(this, SIGNAL(si_load_info_point_file(QString , QString )), listPointWin, SLOT(sl_load_info_point_file(QString , QString)));
    connect(ui->pushButton_synchronizeWithComPort, SIGNAL(clicked(bool)), listPointWin, SLOT(sl_changeSynchronizeMark(bool)));
    connect(this, SIGNAL(si_send_raw_QString_from_currentPort(QString)), terminalWin, SLOT(sl_receive_raw_string(QString)));
    connect(this, SIGNAL(si_send_raw_QString_from_currentPort(QString)), listPointWin, SLOT(sl_receive_raw_string(QString)));

    /// Соединение "ДЕРЕВА ФАЙЛОВ" с "ПРОСМОТРЩИК ФАЙЛОВ"
    connect(treeFilesWin, SIGNAL(si_clear_listFiles()), filesViewerWin, SLOT(sl_clear_listFiles()));
    connect(treeFilesWin, SIGNAL(si_add_fileMetaItem(Class_File_Meta_Item*)), filesViewerWin, SLOT(sl_add_fileMetaItem(Class_File_Meta_Item*)));
    connect(treeFilesWin, SIGNAL(si_show_fileItem(QTreeWidgetItem*)), filesViewerWin, SLOT(sl_show_fileItem(QTreeWidgetItem*)));
    /// Соединение "СПИСКА ТОЧЕК ТРАССИРОВКИ" с "ПРОСМОТРЩИК ФАЙЛОВ"
    connect(listPointWin, SIGNAL(si_show_trace_point_by_info(trace_point_info*)), filesViewerWin, SLOT(sl_show_trace_point_by_info(trace_point_info*)));
}

Main_Win::~Main_Win()
{
    delete ui;
}

void Main_Win::sl_onwin_click()
{
    QDesktopWidget* desktop = QApplication::desktop();
    QRect rect_desktop = desktop->availableGeometry(this);

    //вычисление положения окон
    QRect rect_main(0,0, rect_desktop.width(), this->minimumHeight());
    QRect rect_treeFiles(rect_main.x(), rect_main.y() + rect_main.height(),
                         rect_main.width()*0.15, rect_desktop.height() - rect_main.height());
    QRect rect_filesViewer(rect_main.x() + rect_treeFiles.width(), rect_main.y() + rect_main.height(),
                           rect_main.width()*0.50, rect_desktop.height() - rect_main.height());
    QRect rect_listPoints(rect_main.x() + rect_treeFiles.width() + rect_filesViewer.width(), rect_main.y() + rect_main.height(),
                          rect_desktop.width() - rect_treeFiles.width() - rect_filesViewer.width(), (rect_desktop.height() - rect_main.height())/2);
    QRect rect_terminal(rect_main.x() + rect_treeFiles.width() + rect_filesViewer.width(), rect_main.y() + rect_main.height() + (rect_desktop.height() - rect_main.height())/2,
                        rect_desktop.width() - rect_treeFiles.width() - rect_filesViewer.width(), (rect_desktop.height() - rect_main.height())/2);

    //применение геометрий окон
    this->setGeometry(rect_main);
    treeFilesWin->setGeometry(rect_treeFiles);
    filesViewerWin->setGeometry(rect_filesViewer);
    listPointWin->setGeometry(rect_listPoints);
    terminalWin->setGeometry(rect_terminal);
}

void Main_Win::on_pushButton_treeFilesWin_clicked(bool checked)
{
    treeFilesWin->setVisible(checked);
}

void Main_Win::on_pushButton_terminalWin_clicked(bool checked)
{
    terminalWin->setVisible(checked);
}

void Main_Win::on_pushButton_listPointWin_clicked(bool checked)
{
    listPointWin->setVisible(checked);
}

void Main_Win::on_pushButton_filesViewerWin_clicked(bool checked)
{
    filesViewerWin->setVisible(checked);
}

void Main_Win::on_pushButton_prefencesWin_clicked()
{
    this->prefencesWin = new prefences_win(this);
    this->prefencesWin->show();
    if (this->prefencesWin->result() == 0)
    {
        settings->load();
        if (settings->nameComPort.compare(settings->VirtPortConst) == 0)
        {
            ui->label_sourceData->setText(QString("Источник данных:   %1").arg(settings->VirtPortConst));
        }
        else
        {
            ui->label_sourceData->setText(QString("Источник данных:   %1").arg("COM-X"));
        }
    }
}

void Main_Win::on_pushButton_clear_clicked()
{

}

void Main_Win::on_pushButton_viewAll_clicked()
{
    ui->pushButton_filesViewerWin->setChecked(true);
    ui->pushButton_listPointWin->setChecked(true);
    ui->pushButton_terminalWin->setChecked(true);
    ui->pushButton_treeFilesWin->setChecked(true);
    on_pushButton_filesViewerWin_clicked(true);
    on_pushButton_listPointWin_clicked(true);
    on_pushButton_terminalWin_clicked(true);
    on_pushButton_treeFilesWin_clicked(true);
}

void Main_Win::on_pushButton_aboutApp_clicked()
{
    info_about_app_win* dialog = new info_about_app_win(this);
    dialog->setWindowFlag(Qt::Dialog, true);
    dialog->setWindowModality(Qt::WindowModal);
    dialog->show();
    dialog->result();
}

void Main_Win::on_pushButton_tracePointList_clicked()
{
    if (pointDialog != NULL)
    {
        delete pointDialog;
        pointDialog = NULL;
    }
    pointDialog = new trace_point_proc_dialog(this);
    connect(pointDialog, SIGNAL(s_outListTraceInfo(QString, QList<type_trace_point_info>)), this->listPointWin, SLOT(sl_load_info_point_file(QString, QList<type_trace_point_info>)));
    pointDialog->set_currentPath(this->current_path);
    pointDialog->show();
    emit pointDialog->s_createListTraceInfo();
}

//#include "../../TracingSystemPreprocessor_Solution/TracingSystemPreprocessor/file_trace_points.h"
//#include "../../TracingSystemPreprocessor_Solution/TracingSystemPreprocessor/type_trace_point_info.h"

void Main_Win::on_pushButton_openDirectoryProject_clicked()
{
    App_Settings opt;
    opt.load();

    QString root_name = QFileDialog::getExistingDirectory(this, "Укажите каталог с проектом", opt.lastOpenDir);

    if (root_name.isEmpty()) return;
    ui->label_dirProject->setText(QString("КАТАЛОГ С ПРОЕКТОМ: \"%1\"").arg(root_name));
    opt.lastOpenDir = root_name;
    opt.save();
    treeFilesWin->sl_open_dir_project(root_name);
    //Генерация файла с точками трассировки
    current_path = root_name;
    //ВЫЗОВ ОКНА-МОДУЛЯ
    delete pointDialog;
    ui->pushButton_createTracePointsList->click();
}

void Main_Win::sl_currentComXPort_read_data()
{
    quint64 count = currentPort->bytesAvailable();
    if (count)
    {
        QByteArray byte_array = currentPort->readAll();
        QString raw_string(byte_array);
        emit si_send_raw_QString_from_currentPort(raw_string);
    }
}

void Main_Win::sl_currentVirtualPort_read_data()
{
    quint64 count = virtPort->bytesAvailable();
    if (count)
    {
        QByteArray byte_array = virtPort->readAll();
        QString raw_string(byte_array);
        emit si_send_raw_QString_from_currentPort(raw_string);
    }
}
#include <QPushButton>
void Main_Win::on_start_stop_clicked_virtualPort(bool checked)
{
    if (settings->nameComPort.compare(settings->VirtPortConst) != 0) return;
    if (checked)
    {
        if (listPointWin->get_list_InfoAboutPoints().length() == 0)
        {
            QMessageBox* msg = new  QMessageBox(this);
            msg->setText(QString("Не выбран каталог с проектом!"));
            msg->show();
            ui->pushButton_startTraceFromComPort->setChecked(false);
            return;
        }
        else
        {
            virtPort = new Virtual_Serial_Port(this);
            virtPort->TimeOut = 1500;
            virtPort->list_InfoAboutPoints = this->listPointWin->get_list_InfoAboutPoints();
            ui->label_sourceData->setText(QString("Источник данных:   %1").arg(settings->VirtPortConst));
            connect(virtPort, SIGNAL(readyRead()), this, SLOT(sl_currentVirtualPort_read_data()));
            virtPort->start();
        }
    }
    else
    {
        virtPort->stop();
        disconnect(virtPort, SIGNAL(readyRead()), this, SLOT(sl_currentVirtualPort_read_data()));
        delete virtPort;
        ui->label_sourceData->setText(QString("Источник данных:   %1").arg("\"No data\""));
    }
    manage_buttons();
}

void Main_Win::on_start_stop_clicked_comPort(bool checked)
{
    if (settings->nameComPort.compare(settings->VirtPortConst) == 0) return;
    if (checked)
    {
        QSerialPortInfo* serialInfo = new QSerialPortInfo(settings->nameComPort);
        if (!serialInfo->isValid())
        {
            QMessageBox* msg = new  QMessageBox(this);
            msg->setText(QString("%1 - недопустимый!").arg(settings->nameComPort));
            msg->show();
            ui->pushButton_startTraceFromComPort->setChecked(false);
            return;
        }
        if (serialInfo->isBusy())
        {
            QMessageBox* msg = new  QMessageBox(this);
            msg->setText(QString("%1 - занят!").arg(settings->nameComPort));
            msg->show();
            ui->pushButton_startTraceFromComPort->setChecked(false);
            return;
        }
        currentPort = new QSerialPort(settings->nameComPort, this);
        connect(currentPort, SIGNAL(readyRead()), this, SLOT(sl_currentComXPort_read_data()));
        currentPort->open(QIODevice::ReadWrite);
        currentPort->setParity(QSerialPort::NoParity);
        currentPort->setDataBits(QSerialPort::Data8);
        currentPort->setStopBits(QSerialPort::OneStop);
        currentPort->setFlowControl(QSerialPort::NoFlowControl);
        currentPort->setBaudRate(QSerialPort::Baud115200, QSerialPort::AllDirections);
        currentPort->flush();
        ui->label_sourceData->setText(QString("Источник данных:   %1").arg(settings->nameComPort));
    }
    else
    {
        disconnect(currentPort, SIGNAL(readyRead()), this, SLOT(sl_currentComXPort_read_data()));
        currentPort->close();
        delete currentPort;
        ui->label_sourceData->setText(QString("Источник данных:   %1").arg("\"No data\""));
    }
    manage_buttons();
}

void Main_Win::manage_buttons()
{
    if (ui->pushButton_startTraceFromComPort->isChecked())
    {
        ui->pushButton_prefences->setEnabled(false);
        ui->pushButton_openDirectoryProject->setEnabled(false);
        ui->pushButton_createTracePointsList->setEnabled(false);
    }
    else
    {
        ui->pushButton_prefences->setEnabled(true);
        ui->pushButton_openDirectoryProject->setEnabled(true);
        ui->pushButton_createTracePointsList->setEnabled(true);
    }
}

void Main_Win::set_TitleOfProgram(QString name, QString version)
{
    QString title = QString("\"%1\" - версия %2")
                    .arg(name).arg(version);
    this->setWindowTitle(title);
    ui->label_title->setText(title);
}
