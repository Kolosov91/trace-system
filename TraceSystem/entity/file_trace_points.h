#ifndef FILE_TRACE_POINTS_H
#define FILE_TRACE_POINTS_H

#include <QObject>
#include <QFileInfo>
#include <QDir>
#include <QList>
#include <QTextStream>
#include <QFile>
#include <QTextCodec>
#include <QRegExp>
#include "types/type_trace_point_info.h"

//Класс файла-объекта, содержащего список имён файлов и список точек трассировки,
//а также сохранение-загрузка с диска и на диск
class file_trace_points : public QObject
{
    Q_OBJECT
public:
    explicit file_trace_points(QObject *parent = 0);
    ~file_trace_points();
    void save();//сохранить файл на диск
    void load(QString path);//загрузить файл с диска
    void reset();//сброс содержимого объекта

    //установить полное имя файла с точками трассировки
    void set_fullNameFile(QString value) {fullNameFile = value;}
//    //установить список имён файлов проекта
//    void set_listFiles(QStringList list) {listFiles = list;}
    //установить спсиок точек трассировки
    void set_listTracePoints(QList<type_trace_point_info> list) {listTracePoints = list;}
    QList<type_trace_point_info> get_listTracePoints() {return listTracePoints;}

private:
    QString fullNameFile;//полное имя файла с точками трассировки
//    QStringList listFiles;//список имён файлов проекта "*.c"
    QList<type_trace_point_info> listTracePoints;//список точек трассировки

    QString convertToQString(type_trace_point_info point);//преобразовать из объекта "точка трассировки" в строку
    type_trace_point_info convertFromQString(QString line);//преобразование из строки в объект "точка трассировки"

signals:

public slots:
};

#define filename QString("trace_points") //имя лог-файла

#endif // FILE_TRACE_POINTS_H
