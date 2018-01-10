#include "tree_files_win.h"
#include "ui_tree_files_win.h"

tree_files_win::tree_files_win(QWidget *parent) :
    Base_Dialog(parent),
    ui(new Ui::tree_files_win)
{
    ui->setupUi(this);
    ui->pushButton_close->setIcon(QIcon(QString(":/images/1449324474_delete.png")));
    connect(ui->treeWidget_project, SIGNAL(itemDoubleClicked(QTreeWidgetItem*,int)), this, SLOT(sl_fileItemClicked(QTreeWidgetItem*,int)));
}

tree_files_win::~tree_files_win()
{
    delete ui;
}

void tree_files_win::createTreeProcessing(QTreeWidgetItem *root_item, QDir curDir)
{
    //ОБРАБОТКА ТЕКУЩЕГО КАТАЛОГА
    root_item->setFlags(Qt::ItemIsEnabled);
    root_item->setText(0, curDir.dirName());//имя каталога
    root_item->setIcon(0, QIcon(":/images/1449324516_folder.png"));
    //ОБРАБОТКА ФАЙЛОВ ТЕКУЩЕГО КАТАЛОГА
    QFileInfoList files = curDir.entryInfoList(QStringList{QString("*.c")}, QDir::Files);//список файлов в текущем каталоге с заданной маской фильтрации
    for (int i=0; i < files.length(); i++)
    {
        //ОБРАБОТКА ОДНОГО ФАЙЛА
        QTreeWidgetItem* cur_item_file = new QTreeWidgetItem(root_item);// виджет каталога
        cur_item_file->setFlags(Qt::ItemIsEnabled);
        cur_item_file->setText(0, files.at(i).baseName() + ".c");//имя файла
        cur_item_file->setIcon(0, QIcon(":/images/1449324440_document.png"));
        root_item->addChild(cur_item_file);//добавляем виджет файла на экран

        /*Создаём дескриптор метакласса о файле*/
        Class_File_Meta_Item* meta_item = new Class_File_Meta_Item;
        meta_item->set_filename(files.at(i).absoluteFilePath());
        meta_item->set_p_treeWidget(cur_item_file);
        emit si_add_fileMetaItem(meta_item);
    }
    //ОБРАБОТКА ПОДКАТАЛОГОВ
    QFileInfoList underDirs = curDir.entryInfoList(QDir::AllDirs | QDir::NoDotAndDotDot | QDir::NoSymLinks);//Список подкаталогов в текущем
    for (int i=0; i < underDirs.length(); i++)
    {
        QTreeWidgetItem *sub_item = new QTreeWidgetItem(root_item);
        root_item->addChild(sub_item);
        createTreeProcessing(sub_item, QDir(underDirs.at(i).absoluteFilePath()));
    }
}

void tree_files_win::sl_open_dir_project(QString root_name)
{
    QDir root;//корневой каталог
    root.setPath(root_name);
    QTreeWidget* treeWidget = ui->treeWidget_project;
    treeWidget->clear();
    emit si_clear_listFiles();
    QTreeWidgetItem* root_item = new QTreeWidgetItem(treeWidget);// виджет - корень
    treeWidget->addTopLevelItem(root_item);//добавляем виджет корня на экран
    createTreeProcessing(root_item, root);//рекурсивная обработка каталога и его содержимого
    treeWidget->expandAll();
    treeWidget->resizeColumnToContents(0);
}

void tree_files_win::on_pushButton_close_clicked()
{
    emit si_hide();
}

void tree_files_win::sl_fileItemClicked(QTreeWidgetItem *item, int column)
{
    Q_UNUSED(column);
    emit si_show_fileItem(item);
}
