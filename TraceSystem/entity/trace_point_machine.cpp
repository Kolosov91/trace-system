#include "trace_point_machine.h"

trace_point_machine::trace_point_machine(QObject *parent) : QObject(parent)
{

}

trace_point_machine::~trace_point_machine()
{

}

void trace_point_machine::Start()
{
    this->listFiles.clear();//очистка списка файлов
    this->listTracePoints.clear();//очистка списка точек трасиировки
    dirRootProcessing();//построение списка файлов
    tracePointsProcessing();//построение списка точек и модификация файлов
}

void trace_point_machine::StartOnlyLookingForFiles()
{
    this->listFiles.clear();//очистка списка файлов
    this->listTracePoints.clear();//очистка списка точек трасиировки
    dirRootProcessing();//построение списка файлов
}

void trace_point_machine::dirRootProcessing()
{
    QStringList list_files;//список файлов
    QDir root;//корневой каталог
    root.setPath(this->root_path);
    oneDirProcessing(&list_files, root);//рекурсивная обработка каталога и его подкаталогов
    this->listFiles = list_files;
}

void trace_point_machine::oneDirProcessing(QStringList *list_files, QDir curDir)
{
    //ОБРАБОТКА ТЕКУЩЕГО КАТАЛОГА
    QFileInfoList files = curDir.entryInfoList(QStringList{FILE_C}, QDir::Files);//список файлов в текущем каталоге с заданной маской фильтрации
    for (int i=0; i < files.length(); i++)
        list_files->append(files.at(i).absoluteFilePath());
    //ОБРАБОТКА ТЕКУЩЕГО ПОДКАТАЛОГОВ
    QFileInfoList underDirs = curDir.entryInfoList(QDir::AllDirs | QDir::NoDotAndDotDot | QDir::NoSymLinks);//Список подкаталогов в текущем
    for (int i=0; i < underDirs.length(); i++)
        oneDirProcessing(list_files, QDir(underDirs.at(i).absoluteFilePath()));
}

void trace_point_machine::tracePointsProcessing()
{
    QRegExp trace_regExp = QRegExp("\\bTRACE_POINT+(?=\\()");
    QRegExp lineComment_regExp = QRegExp("//[^\n]*");
    QRegExp commentStartExpression = QRegExp("/\\*");
    QRegExp commentEndExpression = QRegExp("\\*/");
    for(int i=0; i < this->listFiles.length(); i++)
    {
        bool curFileModified = false;//признак модификации(правки) файла
        QStringList lines;//содержимое файла - построчно
        QFile file(listFiles.at(i));//файл
        /*ОТКРЫВАЕМ ФАЙЛ для АНАЛИЗА*/
        if (!file.open(QFile::ReadOnly | QFile::Text)) return;//пытаемся его открыть
        {
            QTextStream stream(&file);//поток для чтения текстового содержимого
            stream.setCodec(QTextCodec::codecForName("Windows-1251"));//"Windows-1251" "UTF-8"
            lines = stream.readAll().split('\n');
            bool isInComment = false;
            for (int ind = 0; ind < lines.length(); ind++)
            {
                QString text = lines.at(ind);//содержимое очередной строки
                if (trace_regExp.indexIn(text) >= 0)
                {
                    int indexPoint = trace_regExp.indexIn(text);//индекс токена - точка трасировки

                    //проверка на многострочные комментарии
                    int indexStartComment = commentStartExpression.indexIn(text);
                    if (indexStartComment>=0)
                        if (indexStartComment < indexPoint)
                        {
                            isInComment = true;
                            int indEndComm = commentEndExpression.indexIn(text);
                            if (indEndComm>=0)
                                if (indEndComm > indexStartComment)
                                    isInComment = false;
                            continue;
                        }

                    if (isInComment)
                    {
                        int indexEndComment = commentEndExpression.indexIn(text);
                        isInComment = false;
                        if (indexEndComment > indexPoint)
                            continue;
                    }

                    int index_commentLine = lineComment_regExp.indexIn(text);//индекс токена - коммент
                    //проверка на нахождение в комментарии
                    if (index_commentLine>=0)
                    if (index_commentLine < indexPoint)
                        continue;
                    int end = text.indexOf(";", indexPoint);//индекс - конец аргументов точки
                    int begin = text.indexOf("(", indexPoint);//индекс - начало аргументов точки
                    QStringList trace_args = text.mid(begin+1, end-begin-2).split(",");//аргументы точки
                    QString arg_id = trace_args.at(0);//идентификатор точки
//                    QString temp = text;
//                    /*Замена идентификатора*/
//                    temp = temp.remove(begin+1, arg_id.length());
//                    temp = temp.insert(begin+1, QString::number(id_trace_point));
//                    lines.replace(ind, temp);
                    type_trace_point_info point;//точка трассировки
                    point.full_name_path = listFiles.at(i);

                    //делаем путь относительным

                    point.full_name_path = point.full_name_path.remove(0, this->root_path.length());

                    point.point_id = arg_id;
                    this->listTracePoints.append(point);//добавляем точку в список
                    curFileModified = false;
                }
            }
        }
        file.close();//закрываем файл
        /*ОТКРЫВАЕМ ФАЙЛ для ПЕРЕЗАПИСИ*/
        if (curFileModified)
        {
            if (!file.open(QFile::WriteOnly | QFile::Text)) return;//пытаемся его открыть
            {
                QTextStream stream(&file);//поток для записи текстового содержимого
                stream.setCodec(QTextCodec::codecForName("Windows-1251"));//"Windows-1251" "UTF-8"
                for (int ind = 0; ind < lines.length(); ind++)
                    stream << lines.at(ind) + "\n";
            }
            file.flush();
            file.close();//закрываем файл
        }
    }
}

