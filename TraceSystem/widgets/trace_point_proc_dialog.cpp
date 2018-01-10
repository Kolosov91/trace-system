#include "trace_point_proc_dialog.h"
#include "ui_trace_point_proc_dialog.h"
#include "entity/trace_point_machine.h"

trace_point_proc_dialog::trace_point_proc_dialog(QWidget *parent) :
    Base_Dialog(parent),
    ui(new Ui::trace_point_proc_dialog)
{
    ui->setupUi(this);
    this->setWindowFlag(Qt::Dialog, true);
    this->setWindowModality(Qt::WindowModal);
    connect(this, SIGNAL(s_createListTraceInfo()), SLOT(sl_createListTraceInfo()));
    connect(ui->pushButton_accept, SIGNAL(clicked(bool)), this, SLOT(on_pushButton_accept()));
}

trace_point_proc_dialog::~trace_point_proc_dialog()
{
    delete ui;
}

void trace_point_proc_dialog::on_pushButton_accept()
{
    emit s_outListTraceInfo(current_path, points);
    this->close();
}

void trace_point_proc_dialog::sl_createListTraceInfo()
{
    if (current_path.isEmpty()) return;
    trace_point_machine machine;//Объект механизма анализа
    machine.set_fullPath(this->current_path);//установка полного пути
    machine.Start();//запуск построения списка файлов, списка точек и модификация файлов проекта
    //int countFiles = machine.get_listFiles().length();//кол-во файлов
    int countTracePoints = machine.get_listTracePoints().length();//кол-во точек трассировки
    ui->lcdNumber->display(countTracePoints);
    points = machine.get_listTracePoints();
    foreach (type_trace_point_info point, points)
    {
        ui->listWidget_points->addItem(QString("%1 --- %2").arg(point.full_name_path, point.point_id));
    }
}
