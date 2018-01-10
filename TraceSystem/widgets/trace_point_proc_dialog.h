#ifndef TRACE_POINT_PROC_DIALOG_H
#define TRACE_POINT_PROC_DIALOG_H

#include <QWidget>
#include "base_win.h"
#include <QList>
#include "types/type_trace_point_info.h"

namespace Ui {
class trace_point_proc_dialog;
}

class trace_point_proc_dialog : public Base_Dialog
{
    Q_OBJECT

public:
    explicit trace_point_proc_dialog(QWidget *parent = 0);
    ~trace_point_proc_dialog();

    void set_currentPath(QString path) { current_path = path; }

signals:
    void s_outListTraceInfo(QString path, QList<type_trace_point_info> points);
    void s_createListTraceInfo();

private slots:
    void on_pushButton_accept();
    void sl_createListTraceInfo();

private:
    Ui::trace_point_proc_dialog *ui;
    QString current_path;
    QList<type_trace_point_info> points;
};

#endif // TRACE_POINT_PROC_DIALOG_H
