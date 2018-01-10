#ifndef LIST_POINT_WIN_H
#define LIST_POINT_WIN_H

#include <QWidget>
#include "base_win.h"
#include "types/trace_point_item.h"
#include <types/type_trace_point_info.h>
#include <QList>
#include <QListWidgetItem>
#include <QListWidget>
#include <QTime>
#include <QDateTime>
#include <QShortcut>

namespace Ui {
class list_point_win;
}

class list_point_win : public Base_Dialog
{
    Q_OBJECT

public:
    explicit list_point_win(QWidget *parent = 0);
    ~list_point_win();
    QList<trace_point_info*> get_list_InfoAboutPoints() {return list_InfoAboutPoints;}

signals:
    void si_show_trace_point_by_info(trace_point_info* info);   //показать точку трассировки по информации о ней

public slots:
    void sl_load_info_point_file(QString path, QList<type_trace_point_info> points);    //Загрузка списка информации о точках
    void sl_receive_raw_string(QString str);                //Принять сырую строку
    void sl_clear_list_trace_points();                      //очистить список точек трассировки
    void sl_changeSynchronizeMark(bool mark) {isSynchronize = mark;}

private slots:
    void on_pushButton_close_clicked();
    void list_itemDoubleClicked(QListWidgetItem * item);    //клик по виджету точки трассировки
    void list_currentRowChanged(int currentRow);
    void sl_key_NextPoint_S();
    void sl_key_PrevPoint_W();
    void sl_key_clearCurrent();
    void sl_key_showPoints();
    void sl_key_gotoSrcCode();

private:
    QShortcut * key_NextPoint_S;
    QShortcut * key_PrevPoint_W;
    QShortcut * key_clearCurrent_F3;
    QShortcut * key_showPoints_F2;
    QShortcut * key_gotoSrcCode_F1;

private:
    enum states_tt {looking_for_begin, looking_for_end};

    Ui::list_point_win *ui;
    QList<trace_point_info*> list_InfoAboutPoints;  //список - информация о точках из файла
    QList<trace_point_item*> list_TracePoints;      //список - точки трассировки фактические
    QString tempBuffer = "";
    trace_point_info* current_InfoPoint = NULL;

    void add_trace_point(QString value_key, qint32 time, qint32 mark, qint32 freq);
    states_tt state = states_tt::looking_for_begin;
    int count_errors = 0;           //кол-во ошибок разбора парсером точек
    bool isSynchronize = false;     //Признак синхронизации (т.е. при появлении новой ТТ будет прокручиваться до неё список)
};

#endif // LIST_POINT_WIN_H
