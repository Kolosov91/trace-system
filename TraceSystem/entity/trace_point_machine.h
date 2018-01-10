#ifndef TRACE_POINT_MACHINE_H
#define TRACE_POINT_MACHINE_H

#include <QObject>
#include <QFileInfo>
#include <QDir>
#include <QList>
#include <QTextStream>
#include <QFile>
#include <QTextCodec>
#include <QRegExp>
#include "types/type_trace_point_info.h"

/*Константы-значения файлов для обработки*/
#define FILE_C          QString("*.c")      //c-файл
#define FILE_H          QString("*.h")      //h-файл
#define FILE_CPP        QString("*.cpp")    //cpp-файл
#define FILE_CS         QString("*.cs")    //cs-файл
/**/

//Класс алгоритма построения списка имён файлов и точкек трассировки,
//а также модификации и сохранения файлов проекта
class trace_point_machine : public QObject
{
    Q_OBJECT
public:
    explicit trace_point_machine(QObject *parent = 0);
    ~trace_point_machine();

    //установить полный путь к проекту
    void set_fullPath(QString value) { root_path = value; }
    //получить список имён файлов проекта
    QStringList get_listFiles() { return listFiles; }
    //получить список с точками трассировки
    QList<type_trace_point_info> get_listTracePoints() {return listTracePoints;}

    void Start();//Запуск - построение списка имён файлов проекта, построение списка точек трассировки, модификация файлов проекта и сохранение на диске
    void StartOnlyLookingForFiles();//Запуск - ТОЛЬКО построение списка имён файлов проекта

private:
    QString root_path;//корневая директория
    QStringList listFiles;//список имен файлов проекта "*.c"
    QList<type_trace_point_info> listTracePoints;//список точек трассировки

    void dirRootProcessing();//Посторение списка файлов
    void oneDirProcessing(QStringList *list_files, QDir curDir);//Рекурсивная обработка одной директории
    void tracePointsProcessing();//Построение списка точек трассировки

signals:

public slots:
};

#endif // TRACE_POINT_MACHINE_H
