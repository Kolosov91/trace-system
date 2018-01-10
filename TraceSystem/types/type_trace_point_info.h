#ifndef TYPE_TRACE_POINT_INFO
#define TYPE_TRACE_POINT_INFO

#include <QString>

//Объект "Точка трассировки"
struct type_trace_point_info
{
    QString full_name_path;//индекс имени файла, в котором расположена точка трассировки
    QString point_id;//уникальный идентификатор точки трассировки

    //оператор присваивания (!нужно для передачи по значению)
    type_trace_point_info& operator=(const type_trace_point_info &obj)
    {
        if (this != &obj)
        {
            full_name_path = obj.full_name_path;
            point_id = obj.point_id;
        }
        return *this;
    }
};

#endif // TYPE_TRACE_POINT_INFO

