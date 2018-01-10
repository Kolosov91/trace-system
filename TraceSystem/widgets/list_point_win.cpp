#include "list_point_win.h"
#include "ui_list_point_win.h"
#include <QMessageBox>
#include <QPixmap>


list_point_win::list_point_win(QWidget *parent) :
    Base_Dialog(parent),
    ui(new Ui::list_point_win)
{
    ui->setupUi(this);
    ui->pushButton_close->setIcon(QIcon(QString(":/images/1449324474_delete.png")));
    connect(ui->listWidget_points, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(list_itemDoubleClicked(QListWidgetItem*)));

    connect(ui->listWidget_points, SIGNAL(currentRowChanged(int)), this, SLOT(list_currentRowChanged(int)));

    // Действие: Предsдущая точка
    key_NextPoint_S = new QShortcut(this);
    key_NextPoint_S->setKey(Qt::Key_S);
    connect(key_NextPoint_S, SIGNAL(activated()), this, SLOT(sl_key_NextPoint_S()));
    connect(ui->pushButton_next, SIGNAL(clicked(bool)), this, SLOT(sl_key_NextPoint_S()));
    // Действие: Следующая точка
    key_PrevPoint_W = new QShortcut(this);
    key_PrevPoint_W->setKey(Qt::Key_W);
    connect(key_PrevPoint_W, SIGNAL(activated()), this, SLOT(sl_key_PrevPoint_W()));
    connect(ui->pushButton_prev, SIGNAL(clicked(bool)), this, SLOT(sl_key_PrevPoint_W()));
    //Действие: "Очистить теткущую точку"
    connect(ui->pushButton_clear_current, SIGNAL(clicked(bool)), this, SLOT(sl_key_clearCurrent()));
    key_clearCurrent_F3 = new QShortcut(this);
    key_clearCurrent_F3->setKey(Qt::Key_F3);
    connect(key_clearCurrent_F3, SIGNAL(activated()), this, SLOT(sl_key_clearCurrent()));
    //Действие: Перейти в исходный код
    connect(ui->pushButton_goto_src_code, SIGNAL(clicked(bool)), this, SLOT(sl_key_gotoSrcCode()));
    key_gotoSrcCode_F1 = new QShortcut(this);
    key_gotoSrcCode_F1->setKey(Qt::Key_F1);
    connect(key_gotoSrcCode_F1, SIGNAL(activated()), this, SLOT(sl_key_gotoSrcCode()));
    //Действие: Показать точки трассировки
    key_showPoints_F2 = new QShortcut(this);
    key_showPoints_F2->setKey(Qt::Key_F2);
    connect(key_showPoints_F2, SIGNAL(activated()), this, SLOT(sl_key_showPoints()));
    connect(ui->pushButton_show_points, SIGNAL(clicked(bool)), this, SLOT(sl_key_showPoints()));
}

list_point_win::~list_point_win()
{
    delete ui;
}

void list_point_win::sl_load_info_point_file(QString path,  QList<type_trace_point_info> points)
{
    this->list_InfoAboutPoints.clear();
    foreach (type_trace_point_info point, points)
    {
        trace_point_info* item = new trace_point_info;
        item->value_key = point.point_id;
        item->filename_full = path + point.full_name_path;
        this->list_InfoAboutPoints.append(item);
    }
    ui->label_info_points->setText(QString(" Файл \"trace_points\" содержит:\n %1 пунктов").arg(QString::number(this->list_InfoAboutPoints.length())));
}

#define ID_TT   QString("TRC*")
#define END_TT  '\n'
#define SEP_TT  '*'

void list_point_win::add_trace_point(QString value_key, qint32 time, qint32 mark, qint32 freq)
{
    trace_point_item* curPoint = new trace_point_item;      //экземпляр точки трасировки
    QListWidgetItem* curWidgetPoint = new QListWidgetItem;  //виджет точки трассирровки
    QString value_key_processing = QString("\"%1\"").arg(value_key);

/*Поиск точки трассировки*/
    bool isFindPoint = false;
    foreach (trace_point_info* curInfoPoint, this->list_InfoAboutPoints)
    {
        if (curInfoPoint->value_key.compare(value_key_processing) == 0)
        {
            isFindPoint = true;
            curPoint->info_point = curInfoPoint;
            curPoint->time = time;
            curPoint->mark = mark;
            curPoint->freq= freq;
            break;
        }
    }
    if (!isFindPoint)
    {
//        QMessageBox::information(this, "Ошибка", "Не найдена точка трассировки");
        count_errors++;
        ui->label_errors->setText(QString("Ошибки распознования точек: %1").arg(QString::number(this->count_errors)));
        return;
    }
/***************************/

    // Вычисляем оценочный параметр
    quint32 bp = curPoint->freq / 5000;
    quint32 ap = (curPoint->freq / 50) % 100;

    if (ap % 10 >= 5)
    {
        ap = (ap / 10) + 1;
    }
    else
    {
        ap = (ap / 10);
    }

    ap *= 10;

    double F_Hz = bp + ap/100.0; //Оценочный параметр
//    for(int i=list_TracePoints.count()-1; i>=0; i--)
//    {
//        trace_point_item* tempItem = list_TracePoints.at(i);
//        if (curPoint->info_point->value_key.compare(tempItem->info_point->value_key) == 0)
//        {
//            quint32 period = curPoint->time - tempItem->time;
//            F_Hz = period/curPoint->freq * 1000;
//            break;
//        }
//    }
    //

    QTime dateTime(0,0,0,0);
    dateTime = dateTime.addMSecs(curPoint->time);
    QString line =  QString("%1 | %2")
                    .arg(dateTime.toString("hh:mm:ss.zzz"))
                    .arg(curPoint->info_point->value_key);
    line = line.leftJustified(50,'.');
    line = line.append(QString("| %1 | %2 Вх/Мс - %3")
                       .arg(QString::number(curPoint->mark))
                       .arg(QString::number(F_Hz))
                       .arg(QString::number(curPoint->freq)));

    curWidgetPoint->setText(line);
    ui->listWidget_points->addItem(curWidgetPoint);
    list_TracePoints.append(curPoint);
    ui->label_countPoints->setText(QString("Количество принятых точек: %1").arg(QString::number(list_TracePoints.length())));
    if (isSynchronize)
        ui->listWidget_points->scrollToBottom();
}

void list_point_win::sl_receive_raw_string(QString str)
{
    tempBuffer = tempBuffer.append(str);

/*Распознавание точки трассировки из текста*/
$PROCESSING:
    switch (state)
    {
        case states_tt::looking_for_begin:
            if (tempBuffer.indexOf(ID_TT) == -1)//Не найдено начало ТТ
            {
               tempBuffer.clear();
               return;
            }
            else//Найдено начало ТТ
            {
                tempBuffer = tempBuffer.remove(0, ID_TT.length());
                state = states_tt::looking_for_end;
                goto $PROCESSING;
            }
        break;
        case states_tt::looking_for_end:
            if (tempBuffer.indexOf(END_TT) == -1)//Не найдено окончание ТТ
            {
                return;
            }
            else//Найдено окончание ТТ
            {
                QString value_raw_tt = tempBuffer.left(tempBuffer.indexOf(END_TT)+1);
                tempBuffer = tempBuffer.remove(0, value_raw_tt.length());
                value_raw_tt = value_raw_tt.trimmed();
                state = states_tt::looking_for_begin;
                int tempInd = -1;
                bool isGood = false;
                //поиск времени
                tempInd = value_raw_tt.indexOf(SEP_TT);
                if (tempInd == -1) goto $PROCESSING;
                isGood = false;
                qint32 time = value_raw_tt.left(tempInd).toULong(&isGood);
                if (!isGood) goto $PROCESSING;
                value_raw_tt = value_raw_tt.remove(0, tempInd+1);
                //поиск ЧАСТОТЫ
                tempInd = value_raw_tt.lastIndexOf(SEP_TT);
                if (tempInd == -1) goto $PROCESSING;
                isGood = false;
                qint32 freq = value_raw_tt.right(value_raw_tt.length() - tempInd - 1).toULong(&isGood);
                if (!isGood) goto $PROCESSING;
                value_raw_tt = value_raw_tt.remove(tempInd, value_raw_tt.length()-tempInd);
                //поиск метки
                tempInd = value_raw_tt.lastIndexOf(SEP_TT);
                if (tempInd == -1) goto $PROCESSING;
                isGood = false;
                qint32 mark = value_raw_tt.right(value_raw_tt.length() - tempInd - 1).toULong(&isGood);
                if (!isGood) goto $PROCESSING;
                value_raw_tt = value_raw_tt.remove(tempInd, value_raw_tt.length()-tempInd);
                //поиск ключа

                add_trace_point(value_raw_tt, time, mark, freq);
                goto $PROCESSING;
            }
        break;
    }
/**************************/
}

void list_point_win::sl_clear_list_trace_points()
{
    for(int i=0; i< list_TracePoints.count(); i++)
    {
        delete list_TracePoints[i];
    }
    ui->listWidget_points->clear();
    list_TracePoints.clear();
    count_errors = 0;
}

void list_point_win::on_pushButton_close_clicked()
{
    emit si_hide();
}

#include <QSplashScreen>
extern QSplashScreen* splash;

void list_point_win::list_itemDoubleClicked(QListWidgetItem *item)
{
    Q_UNUSED(item);
    splash = new QSplashScreen();
    splash->showFullScreen();
    splash->showMessage(QString("Поиск ТТ в файле..."), Qt::AlignCenter, Qt::green);
    QApplication::flush();
    int current_index = ui->listWidget_points->currentRow();
    trace_point_item* current_point = this->list_TracePoints.at(current_index);
    emit si_show_trace_point_by_info(current_point->info_point);
}

void list_point_win::list_currentRowChanged(int currentRow)
{
    if ((currentRow == -1))
    {
        ui->pushButton_show_points->setEnabled(false);
        ui->pushButton_goto_src_code->setEnabled(false);
    }
    else
    {
        ui->pushButton_show_points->setEnabled(true);
        ui->pushButton_goto_src_code->setEnabled(true);
    }
    if (current_InfoPoint == NULL)
    {
        ui->pushButton_clear_current->setEnabled(false);
        ui->pushButton_next->setEnabled(false);
        ui->pushButton_prev->setEnabled(false);
    }
    else
    {
        ui->pushButton_clear_current->setEnabled(true);
        ui->pushButton_next->setEnabled(true);
        ui->pushButton_prev->setEnabled(true);
    }
}

void list_point_win::sl_key_NextPoint_S()
{
    if (ui->listWidget_points->count() <= 0) return;
    if (ui->listWidget_points->currentRow() == ui->listWidget_points->count() - 1) return;
    ui->listWidget_points->setCurrentRow(ui->listWidget_points->currentRow()+1);
    list_itemDoubleClicked(ui->listWidget_points->currentItem());
}

void list_point_win::sl_key_PrevPoint_W()
{
    if (ui->listWidget_points->count() <= 0) return;
    if (ui->listWidget_points->currentRow() == - 1) return;
    ui->listWidget_points->setCurrentRow(ui->listWidget_points->currentRow()-1);
    list_itemDoubleClicked(ui->listWidget_points->currentItem());
}

void list_point_win::sl_key_clearCurrent()
{

    ui->listWidget_points->setCurrentRow(-1);
    current_InfoPoint = NULL;
    list_currentRowChanged(-1);
    sl_key_showPoints();
}

void list_point_win::sl_key_showPoints()
{
    if (splash == 0) splash = new QSplashScreen(this, QPixmap(":/images/red_bug.ico"));
    splash->show();
    int index = ui->listWidget_points->currentRow();

    if (index != -1)
        current_InfoPoint = this->list_TracePoints.at(index)->info_point;
    int countPoints = ui->listWidget_points->count();
    list_currentRowChanged(index);
    for(int i=0; i < countPoints; i++)
    {
        trace_point_item* item = this->list_TracePoints.at(i);
        if (current_InfoPoint == NULL)
        {
            ui->listWidget_points->item(i)->setBackgroundColor(Qt::white);
            continue;
        }
        if (item->info_point->value_key.compare(current_InfoPoint->value_key) == 0)
        {
            ui->listWidget_points->item(i)->setBackgroundColor(QColor::fromRgb(0xFFFF99));
        }
        else
        {
            ui->listWidget_points->item(i)->setBackgroundColor(Qt::white);
        }
    }
    splash->hide();
}

void list_point_win::sl_key_gotoSrcCode()
{
    list_itemDoubleClicked(NULL);
}



