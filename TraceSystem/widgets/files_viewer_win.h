#ifndef FILES_VIEWER_WIN_H
#define FILES_VIEWER_WIN_H

#include <QWidget>
#include "base_win.h"
#include <QList>
#include "types/class_file_meta_item.h"
#include "entity/clang_trace_highlighter.h"
#include "types/trace_point_item.h"

namespace Ui {
class files_viewer_win;
}

class files_viewer_win : public Base_Dialog
{
    Q_OBJECT

public:
    explicit files_viewer_win(QWidget *parent = 0);
    ~files_viewer_win();

public slots:
    void sl_clear_listFiles();//чистка списка файлов текущих
    void sl_add_fileMetaItem(Class_File_Meta_Item* item);//добавить файл в список
    void sl_show_fileItem(QTreeWidgetItem* p_treeItem);//показать файл
    void sl_show_trace_point_by_info(trace_point_info* info);   //показать точку трассировки по информации о ней
    void on_click_changeEncoding();

private:
    void read_file(QTextEdit* wgt, QString name, QString encoding);

private slots:
    void on_pushButton_close_clicked();     //кнопка закрыть форму
    void tabCloseRequested(int index);      //закрытие вкладки
    void tabCurrentChanged(int index);      //Изменение текущей вкладки

private:
    Ui::files_viewer_win *ui;
    QList<Class_File_Meta_Item*> listFiles;//список файлов проекта

};

#endif // FILES_VIEWER_WIN_H
