#ifndef TRACE_POINT_INFO_H
#define TRACE_POINT_INFO_H

#include <QObject>

class trace_point_info : public QObject
{
    Q_OBJECT
public:
    explicit trace_point_info(QObject *parent = 0);
    ~trace_point_info();

    trace_point_info(const trace_point_info &obj);//Конструктор копирования
    trace_point_info & operator=(const trace_point_info &obj);//Оператор присваивания

    QString value_key;      //уникальный ключ точки трассировки
    QString filename_full;  //полное имя файла, где расположена точка трассировки

signals:

public slots:
};

#endif // TRACE_POINT_INFO_H
