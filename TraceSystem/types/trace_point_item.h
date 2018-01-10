#ifndef TRACE_POINT_ITEM_H
#define TRACE_POINT_ITEM_H

#include <QObject>
#include <QWidget>
#include "trace_point_info.h"

class trace_point_item : public QObject
{
    Q_OBJECT
public:
    explicit trace_point_item(QObject *parent = 0);
    ~trace_point_item();

    trace_point_item(const trace_point_item &obj);//Конструктор копирования
    trace_point_item & operator=(const trace_point_item &obj);//Оператор присваивания

    trace_point_info* info_point;   //указатель на информацию о точке трасировке
    qint32 time;                    //время
    qint32 mark;                    //числовая метка
    qint32 freq;
    QWidget* widget_point;          //указатель на виджет в QListWidget

signals:

public slots:
};

#endif // TRACE_POINT_ITEM_H
