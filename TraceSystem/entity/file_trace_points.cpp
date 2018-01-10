#include "file_trace_points.h"

file_trace_points::file_trace_points(QObject *parent) : QObject(parent)
{

}

file_trace_points::~file_trace_points()
{

}

void file_trace_points::save()
{
    QFile file(this->fullNameFile);//файл
    /*ОТКРЫВАЕМ ФАЙЛ для ПЕРЕЗАПИСИ*/
    if (!file.open(QFile::WriteOnly | QFile::Text)) return;//пытаемся его открыть
    {
        QTextStream stream(&file);//поток для записи текстового содержимого
        stream.setCodec(QTextCodec::codecForName("Windows-1251"));//"Windows-1251" "UTF-8"
        for(int i = 0; i < this->listTracePoints.length(); i++)
        {
            type_trace_point_info point = this->listTracePoints.at(i);
            QString line = convertToQString(point);
            if (i != this->listTracePoints.length()-1) line += "\n";
            stream << line;
        }
    }
    file.flush();
    file.close();//закрываем файл
}

void file_trace_points::load(QString path)
{
    this->listTracePoints.clear();
    QFile file(this->fullNameFile);//файл
    /*ОТКРЫВАЕМ ФАЙЛ для АНАЛИЗА*/
    if (!file.open(QFile::ReadOnly | QFile::Text)) return;//пытаемся его открыть
    {
        QTextStream stream(&file);//поток для записи текстового содержимого
        stream.setCodec(QTextCodec::codecForName("Windows-1251"));//"Windows-1251" "UTF-8"
        QStringList lines = stream.readAll().split('\n');
        for(int i = 0; i < lines.length(); i++)
        {
            type_trace_point_info point = convertFromQString(lines.at(i));
            point.full_name_path = path + "/" + point.full_name_path;
            this->listTracePoints.append(point);
        }
    }
    file.close();//закрываем файл
}

void file_trace_points::reset()
{
    this->listTracePoints.clear();
    this->fullNameFile.clear();
}

QString file_trace_points::convertToQString(type_trace_point_info point)
{
    QString line = QString("%1*%2").arg(point.full_name_path,
                                        point.point_id);
    return line;
}

type_trace_point_info file_trace_points::convertFromQString(QString line)
{
    type_trace_point_info point;
    int index = line.indexOf('*');
    QString fileName = line.left(index);
    QString keyPoint = line.right(line.length() - index-1);

    point.full_name_path = fileName;
    point.point_id = keyPoint;
    return point;
}

