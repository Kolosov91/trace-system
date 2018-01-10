#ifndef CLASS_FILE_META_ITEM_H
#define CLASS_FILE_META_ITEM_H

#include <QObject>
#include <QWidget>
#include <QTreeWidget>
#include <QTextEdit>
#include "entity/clang_trace_highlighter.h"

#define ENCODING_ANSI QString("Windows-1251")
#define ENCODING_UTF8 QString("UTF-8")

//Класс, полностью опиывающий сущность файла (как сам файл, так и его виджеты)
class Class_File_Meta_Item : public QObject
{
    Q_OBJECT
public:
    explicit Class_File_Meta_Item(QObject *parent = 0);
    ~Class_File_Meta_Item();

    Class_File_Meta_Item(const Class_File_Meta_Item &obj);//Конструктор копирования
    Class_File_Meta_Item & operator=(const Class_File_Meta_Item &obj);//Оператор присваивания

    void set_filename(QString name) {filenameFull = name;}
    QString get_filename() {return filenameFull;}

    void set_p_treeWidget(QTreeWidgetItem* p) { p_treeWidget = p;}
    QTreeWidgetItem* get_p_treeWidget() {return p_treeWidget;}

    void set_p_tabWidget(QWidget* p) { p_tabWidget = p;}
    QWidget* get_p_tabWidget() {return p_tabWidget;}

    void set_p_textView(QTextEdit* p) { p_textView = p;}
    QTextEdit* get_p_textView() {return p_textView;}

    void set_p_highlight(clang_trace_highlighter* p) {p_highlight = p;}
    clang_trace_highlighter* get_p_highlight() {return p_highlight;}

    void set_encodingOfFile(QString encoding) {encodingOfFile = encoding;}
    QString get_encodingOfFile() {return encodingOfFile;}

signals:

public slots:

private:
    QString filenameFull;               //полное имя файла
    QTreeWidgetItem* p_treeWidget;      //ссылка на виджет дерева
    QWidget* p_tabWidget;               //ссылка на страницу tabWidget
    QTextEdit* p_textView;              //ссылка на виджет с текстом
    clang_trace_highlighter* p_highlight;   //ссылка на сущность посветки ситаксиса
    QString encodingOfFile;
};

#endif // CLASS_FILE_META_ITEM_H
