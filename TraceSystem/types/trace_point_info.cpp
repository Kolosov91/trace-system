#include "trace_point_info.h"

trace_point_info::trace_point_info(QObject *parent) : QObject(parent)
{

}

trace_point_info::~trace_point_info()
{

}

trace_point_info::trace_point_info(const trace_point_info &obj): QObject()
{
    this->value_key = obj.value_key;
    this->filename_full = obj.filename_full;
}

trace_point_info &trace_point_info::operator=(const trace_point_info &obj)
{
    if (this != &obj)//проверка на ссылку на самого себя
    {
        this->value_key = obj.value_key;
        this->filename_full = obj.filename_full;
    }
    return *this;
}

