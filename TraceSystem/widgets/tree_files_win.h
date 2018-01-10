#ifndef TREE_FILES_WIN_H
#define TREE_FILES_WIN_H

#include <QWidget>
#include "base_win.h"
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QMainWindow>
#include <QTimer>
#include <QList>
#include <QMutex>
#include <QThread>
#include <QtSerialPort/QtSerialPort>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QMessageBox>
#include <QFileDialog>
#include <QTextStream>
#include "types/class_file_meta_item.h"

namespace Ui {
class tree_files_win;
}

class tree_files_win : public Base_Dialog
{
    Q_OBJECT

public:
    explicit tree_files_win(QWidget *parent = 0);
    ~tree_files_win();

private:
    void createTreeProcessing(QTreeWidgetItem *root_item, QDir curDir);

signals:
    void si_clear_listFiles();
    void si_add_fileMetaItem(Class_File_Meta_Item* item);
    void si_show_fileItem(QTreeWidgetItem* p_treeItem);

public slots:
    void sl_open_dir_project(QString root_name);

private slots:
    void on_pushButton_close_clicked();
    void sl_fileItemClicked(QTreeWidgetItem * item, int column);

private:
    Ui::tree_files_win *ui;
};

#endif // TREE_FILES_WIN_H
