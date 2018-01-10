#include "files_viewer_win.h"
#include "ui_files_viewer_win.h"
#include <QFile>
#include <QTextStream>
#include <QTextCodec>
#include <QScrollBar>

files_viewer_win::files_viewer_win(QWidget *parent) :
    Base_Dialog(parent),
    ui(new Ui::files_viewer_win)
{
    ui->setupUi(this);
    ui->pushButton_close->setIcon(QIcon(QString(":/images/1449324474_delete.png")));
    ui->tabWidget_files->clear();
    connect(ui->tabWidget_files, SIGNAL(tabCloseRequested(int)), this, SLOT(tabCloseRequested(int)));

    connect(ui->tabWidget_files, SIGNAL(currentChanged(int)), this, SLOT(tabCurrentChanged(int)));
    connect(ui->pushButton_changeEncoding, SIGNAL(clicked()), this, SLOT(on_click_changeEncoding()));
}

files_viewer_win::~files_viewer_win()
{
    delete ui;
}

void files_viewer_win::sl_clear_listFiles()
{
    listFiles.clear();
    ui->tabWidget_files->clear();
}

void files_viewer_win::sl_add_fileMetaItem(Class_File_Meta_Item *item)
{
    listFiles.append(item);
}

void files_viewer_win::sl_show_fileItem(QTreeWidgetItem *p_treeItem)
{
    foreach (Class_File_Meta_Item* meta_item, this->listFiles)
    {
        if (meta_item->get_p_treeWidget() == p_treeItem)
        {
            if (meta_item->get_p_tabWidget() != NULL)
            {
                ui->tabWidget_files->setCurrentWidget(meta_item->get_p_tabWidget());
            }
            else
            {
                QWidget* tab = new QWidget(ui->tabWidget_files);    //Страница таба
                ui->tabWidget_files->addTab(tab, QIcon(":/images/1449324440_document.png"),
                                            meta_item->get_filename().split('/').last());//добавляем её

            /*НАСТРОЙКА TextEdit'a*/
                QTextEdit* textEdit = new QTextEdit(tab);   //виджет текста
                textEdit->setObjectName(QString("textViewerWidget"));
                textEdit->setReadOnly(true);
                textEdit->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
                textEdit->setLineWrapMode(QTextEdit::NoWrap);   //Запрет переноса строк - т.е. будет появляться горизонтальный скроллбар
                QFont font;
                font.setFamily("Courier New");
                font.setFixedPitch(true);
                font.setPointSize(8);
                textEdit->setFont(font);
            /**********************/

                clang_trace_highlighter* highlighter = new clang_trace_highlighter(textEdit->document());

                QGridLayout* layout = new QGridLayout(tab); //менеджер компоновки
                tab->setLayout(layout);//добавляем виджет текста на экран
                layout->addWidget(textEdit);

                //Добавляем ссылки в метаобейкт файла
                meta_item->set_p_tabWidget(tab);
                meta_item->set_p_textView(textEdit);
                meta_item->set_p_highlight(highlighter);

                //Считываем файл с диска и выводим на экран
                read_file(meta_item->get_p_textView(), meta_item->get_filename(), meta_item->get_encodingOfFile());
                ui->tabWidget_files->setCurrentWidget(tab);
            }
            break;
        }
    }
}

#include <QSplashScreen>
extern QSplashScreen* splash;

void files_viewer_win::sl_show_trace_point_by_info(trace_point_info *info)
{
    foreach (Class_File_Meta_Item* curItem, this->listFiles)
    {
        if (curItem->get_filename().compare(info->filename_full) == 0)
        {  
            sl_show_fileItem(curItem->get_p_treeWidget());
            curItem->get_p_highlight()->current_keyword_trace_point = info->value_key;
            curItem->get_p_highlight()->setDocument(curItem->get_p_textView()->document());
            /*скроллинг*/
            QStringList lines = curItem->get_p_textView()->toPlainText().split('\n');

            //double one_h = curItem->get_p_textView()->verticalScrollBar()->maximum() / (double)(lines.length());
//            title = QString("one_h [%1] = scrollMax [%2] / len [%3]")
//                    .arg(QString::number(one_h))
//                    .arg(QString::number(ui->textEdit_c_example->verticalScrollBar()->maximum()))
//                    .arg(QString::number(lines.length()));
            int len = lines.length();
            for (int i = 0; i < len; i++)
                if (lines.at(i).indexOf(info->value_key)>0)
                {
                    //int val = one_h * i;// + 20*one_h;
                    int max = curItem->get_p_textView()->verticalScrollBar()->maximum();
                    int val = max/len * i;
                    curItem->get_p_textView()->verticalScrollBar()->setValue(val+max/len*5);
//                    title += " --- " + QString("val = %1").arg(QString::number(val));
                    break;
                }
//            curItem->get_p_highlight()->setDocument(curItem->get_p_textView()->document());
            break;
        }
    }
    if (splash != NULL)
        splash->close();
    delete splash;
    splash = NULL;
}

void files_viewer_win::on_click_changeEncoding()
{
    QWidget* widget = ui->tabWidget_files->currentWidget();
    foreach (Class_File_Meta_Item* item, listFiles)
        if (item->get_p_tabWidget() == widget)
        {
            if (item->get_encodingOfFile().compare(ENCODING_ANSI) == 0)
            {
                item->set_encodingOfFile(ENCODING_UTF8);
                ui->pushButton_changeEncoding->setIcon(QIcon(QString(":/images/utf-8.png")));
            }
            else
                if (item->get_encodingOfFile().compare(ENCODING_UTF8) == 0)
                {
                    item->set_encodingOfFile(ENCODING_ANSI);
                    ui->pushButton_changeEncoding->setIcon(QIcon(QString(":/images/ansi.png")));
                }

            ////////
            //Считываем файл с диска и выводим на экран
            if (item->get_p_textView() == NULL) return;
            read_file(item->get_p_textView(), item->get_filename(), item->get_encodingOfFile());
            item->get_p_highlight()->setDocument(item->get_p_textView()->document());
            ////////

            return;
        }
}

void files_viewer_win::read_file(QTextEdit *wgt, QString name, QString encoding)
{
    if (NULL == wgt) return;
    //Считываем файл с диска и выводим на виджет
    QFile file(name);
    if (!file.open(QFile::ReadOnly | QFile::Text)) return;//пытаемся его открыть
    {
        QTextStream stream(&file);//поток для чтения текстового содержимого
        stream.setCodec(QTextCodec::codecForName(encoding.toLatin1()));
        wgt->setText(stream.readAll().replace('\t',"  "));
    }
    file.close();//закрываем файл
}

void files_viewer_win::on_pushButton_close_clicked()
{
    emit si_hide();
}

void files_viewer_win::tabCloseRequested(int index)
{
    QWidget* tab = ui->tabWidget_files->widget(index);
    foreach (Class_File_Meta_Item* meta_item, this->listFiles)
    {
        if (meta_item->get_p_tabWidget() == tab)
        {
            delete meta_item->get_p_highlight();
            meta_item->set_p_highlight(NULL);
            delete meta_item->get_p_textView();
            meta_item->set_p_textView(NULL);
            delete meta_item->get_p_tabWidget();
            meta_item->set_p_tabWidget(NULL);
            break;
        }
    }
}

void files_viewer_win::tabCurrentChanged(int index)
{
    Q_UNUSED(index);
    QWidget* widget = ui->tabWidget_files->widget(index);
    foreach (Class_File_Meta_Item* item, listFiles)
        if (item->get_p_tabWidget() == widget)
        {
            if (item->get_encodingOfFile().compare(ENCODING_UTF8) == 0)
                ui->pushButton_changeEncoding->setIcon(QIcon(QString(":/images/utf-8.png")));
            else
                if (item->get_encodingOfFile().compare(ENCODING_ANSI) == 0)
                    ui->pushButton_changeEncoding->setIcon(QIcon(QString(":/images/ansi.png")));
            break;
        }
}
