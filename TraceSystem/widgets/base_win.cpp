#include "base_win.h"
#include <QPushButton>
#include <QMouseEvent>

Base_Win::Base_Win(QWidget *parent) : QMainWindow(parent)
{
    this->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);     //безрамочный вид
    this->setMouseTracking(true);                                   //всегда отслеживать мышь

}

Base_Win::~Base_Win()
{

}

void Base_Win::sl_button_close_clicked()
{
    this->close();
}

void Base_Win::sl_button_onwin_clicked()
{
    if (this->windowState() == Qt::WindowNoState)
    {
        this->setWindowState(Qt::WindowMaximized);
    }
    else
    {
        this->setWindowState(Qt::WindowNoState);
    }
}

void Base_Win::sl_button_minimize_clicked()
{
   this->setWindowState(Qt::WindowMinimized);
}

void Base_Win::mousePressEvent(QMouseEvent *e)
{
    if (e->buttons() & Qt::LeftButton)  //отслеживаем нажатие ЛКМ
    {
        if (((width() - e->x()) < 30) && ((height() - e->y()) < 30))
        {//если в правом нижнем углу - вкл. режим изменения размера
            dx = e->globalX();
            dy = e->globalY();
            current_mode = win_modes_enum::RESIZE_MODE;
            setCursor( Qt::SizeAllCursor );
        }
        else
        {//если в любом другом месте над формой - вкл. режим перемещения
            dx = e->x();
            dy = e->y();
            current_mode = win_modes_enum::MOUSE_MOVE_MODE;
            setCursor( Qt::OpenHandCursor );
        }
    }
}

void Base_Win::mouseReleaseEvent(QMouseEvent *)
{//при отпускании ЛКМ сбросить все режимы
    setCursor( Qt::ArrowCursor );
    current_mode = win_modes_enum::NO_MODE;
}

void Base_Win::mouseMoveEvent(QMouseEvent *e)
{
    if (e->buttons() == Qt::NoButton)
    {//Если не нажаты кнопки мыши
        if (((width() - e->x()) < 30) && ((height() - e->y()) < 30))
            setCursor( Qt::SizeFDiagCursor );
        else
            setCursor( Qt::ArrowCursor );
    }
    if (e->buttons() & Qt::LeftButton)
    {//если нажата ЛКМ
        switch (current_mode)
        {
            case win_modes_enum::NO_MODE: return;
            case win_modes_enum::RESIZE_MODE:       //режим изменения размера
            {
                pdx = dx; pdy = dy;
                dx = e->globalX();
                dy = e->globalY();
                int deltaX = dx - pdx;
                int deltaY = dy - pdy;
                setGeometry(
                            this->pos().x(),
                            this->pos().y(),
                            width() + deltaX,
                            height()+ deltaY
                            );
            }
            break;
        case win_modes_enum::MOUSE_MOVE_MODE:   //режим перемещения
            {
                setGeometry(
                            pos().x() + (e->x() - dx),
                            pos().y() + (e->y() - dy),
                            width(), height()
                            );
            }
            break;
        }
    }
}

/***************************************************************************************/

Base_Dialog::Base_Dialog(QWidget *parent) : QDialog(parent)
{
    this->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);     //безрамочный вид
    this->setMouseTracking(true);                                   //всегда отслеживать мышь
}

Base_Dialog::~Base_Dialog()
{

}

void Base_Dialog::sl_button_close_clicked()
{
    this->close();
}

void Base_Dialog::sl_button_onwin_clicked()
{
    if (this->windowState() == Qt::WindowNoState)
    {
        this->setWindowState(Qt::WindowMaximized);
    }
    else
    {
        this->setWindowState(Qt::WindowNoState);
    }
}

void Base_Dialog::sl_button_minimize_clicked()
{
   this->setWindowState(Qt::WindowMinimized);
}

void Base_Dialog::mousePressEvent(QMouseEvent *e)
{
    if (e->buttons() & Qt::LeftButton)  //отслеживаем нажатие ЛКМ
    {
        if (((width() - e->x()) < 30) && ((height() - e->y()) < 30))
        {//если в правом нижнем углу - вкл. режим изменения размера
            dx = e->globalX();
            dy = e->globalY();
            current_mode = win_modes_enum::RESIZE_MODE;
            setCursor( Qt::SizeAllCursor );
        }
        else
        {//если в любом другом месте над формой - вкл. режим перемещения
            dx = e->x();
            dy = e->y();
            current_mode = win_modes_enum::MOUSE_MOVE_MODE;
            setCursor( Qt::OpenHandCursor );
        }
    }
}

void Base_Dialog::mouseReleaseEvent(QMouseEvent *)
{//при отпускании ЛКМ сбросить все режимы
    setCursor( Qt::ArrowCursor );
    current_mode = win_modes_enum::NO_MODE;
}

void Base_Dialog::mouseMoveEvent(QMouseEvent *e)
{
    if (e->buttons() == Qt::NoButton)
    {//Если не нажаты кнопки мыши
        if (((width() - e->x()) < 30) && ((height() - e->y()) < 30))
            setCursor( Qt::SizeFDiagCursor );
        else
            setCursor( Qt::ArrowCursor );
    }
    if (e->buttons() & Qt::LeftButton)
    {//если нажата ЛКМ
        switch (current_mode)
        {
            case win_modes_enum::NO_MODE: return;
            case win_modes_enum::RESIZE_MODE:       //режим изменения размера
            {
                pdx = dx; pdy = dy;
                dx = e->globalX();
                dy = e->globalY();
                int deltaX = dx - pdx;
                int deltaY = dy - pdy;
                setGeometry(
                            this->pos().x(),
                            this->pos().y(),
                            width() + deltaX,
                            height()+ deltaY
                            );
            }
            break;
        case win_modes_enum::MOUSE_MOVE_MODE:   //режим перемещения
            {
                setGeometry(
                            pos().x() + (e->x() - dx),
                            pos().y() + (e->y() - dy),
                            width(), height()
                            );
            }
            break;
        }
    }
}
