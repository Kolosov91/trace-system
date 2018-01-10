#include "trace_point_item.h"

trace_point_item::trace_point_item(QObject *parent) : QObject(parent)
{
    this->info_point = NULL;
    this->widget_point = NULL;
}

trace_point_item::~trace_point_item()
{
    delete this->widget_point;
}

trace_point_item::trace_point_item(const trace_point_item &obj): QObject()
{
    this->info_point = obj.info_point;
    this->time = obj.time;
    this->mark = obj.mark;
    this->freq = obj.freq;
    this->widget_point = obj.widget_point;
}

trace_point_item &trace_point_item::operator=(const trace_point_item &obj)
{
    if (this != &obj)//проверка на ссылку на самого себя
    {
        this->info_point = obj.info_point;
        this->time = obj.time;
        this->mark = obj.mark;
        this->freq = obj.freq;
        this->widget_point = obj.widget_point;
    }
    return *this;
}

