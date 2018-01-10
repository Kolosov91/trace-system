#ifndef MAIN_WIN_H
#define MAIN_WIN_H

#include <QMainWindow>
#include "base_win.h"
#include <QDesktopWidget>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QMainWindow>
#include <QTimer>
#include <QList>
#include <QMutex>
#include <QThread>
#include <QtSerialPort/QtSerialPort>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QMessageBox>
#include <QFileDialog>
#include <QTextStream>


#include "tree_files_win.h"     //Окно - Дерево файлов проекта
#include "files_viewer_win.h"   //Окно - Просмотр файлов
#include "list_point_win.h"     //Окно - Список точек трассировки
#include "terminal_win.h"       //Окно - Терминал
#include "prefences_win.h"
#include "trace_point_proc_dialog.h"
#include "info_about_app_win.h"
#include "entity\virtual_serial_port.h"
#include "entity\app_settings.h"
#include "widgets\widget_system_buttons.h"

namespace Ui {
class Main_Win;
}

class Main_Win : public Base_Win
{
    Q_OBJECT

public:
    explicit Main_Win(QWidget *parent = 0);
    ~Main_Win();
    void set_TitleOfProgram(QString name, QString version);

signals:
    void si_load_info_point_file(QString path, QString name_file);
    void si_send_raw_QString_from_currentPort(QString str);

private:
    void createTreeProcessing(QTreeWidgetItem *item, QDir curDir);

public slots:
    void sl_onwin_click();

private slots:
    void on_pushButton_treeFilesWin_clicked(bool checked);
    void on_pushButton_terminalWin_clicked(bool checked);
    void on_pushButton_listPointWin_clicked(bool checked);
    void on_pushButton_filesViewerWin_clicked(bool checked);
    void on_pushButton_prefencesWin_clicked();
    void on_pushButton_clear_clicked();
    void on_pushButton_viewAll_clicked();
    void on_pushButton_aboutApp_clicked();
    void on_pushButton_tracePointList_clicked();

    void on_pushButton_openDirectoryProject_clicked();
    void sl_currentVirtualPort_read_data();
    void sl_currentComXPort_read_data();

    void on_start_stop_clicked_virtualPort(bool checked);
    void on_start_stop_clicked_comPort(bool checked);
    void manage_buttons();

private:
    Ui::Main_Win *ui;

    tree_files_win*     treeFilesWin;
    files_viewer_win*   filesViewerWin;
    list_point_win*     listPointWin;
    terminal_win*       terminalWin;
    prefences_win*      prefencesWin = NULL;
    trace_point_proc_dialog* pointDialog = NULL;

    QString current_path;

    Virtual_Serial_Port* virtPort = NULL;
    QSerialPort* currentPort = NULL;
    App_Settings* settings = NULL;
};

#endif // MAIN_WIN_H
