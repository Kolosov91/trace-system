#ifndef BASE_WIN_H
#define BASE_WIN_H

#include <QMainWindow>
#include "widget_system_buttons.h"
#include <QDialog>

class Base_Win : public QMainWindow
{
    Q_OBJECT
public:
    explicit Base_Win(QWidget *parent = 0);
    ~Base_Win();

private:
    int dx = 0;     //delta координат окна по X в режиме перемещения
    int dy = 0;     //delta координат окна по Y в режиме перемещения
    int pdx = 0;    //delta размеров окна по X в режиме изменения размера
    int pdy = 0;    //delta размеров окна по Y в режиме изменения размера

    //режимы окна
    enum win_modes_enum {NO_MODE /*Нет режима*/ = -1,
                         RESIZE_MODE /*Режим - изменение размера*/,
                         MOUSE_MOVE_MODE /*Режим - перетаскивание*/ };

    win_modes_enum current_mode = win_modes_enum::NO_MODE;//текущий режим окна

    bool isResize = false;      //признак режима изменения размера
    bool isMouseMove = false;   //признак режима перемещения

public slots:
    void sl_button_close_clicked();         //нажатие кнопки - закрыть
    void sl_button_onwin_clicked();         //нажатие кнопки - весь экран/норма
    void sl_button_minimize_clicked();      //нажатие кнопки - минимизировать

    // QWidget interface
protected:
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *e);
};

class Base_Dialog : public QDialog
{
    Q_OBJECT
public:
    explicit Base_Dialog(QWidget *parent = 0);
    ~Base_Dialog();

private:
    int dx = 0;     //delta координат окна по X в режиме перемещения
    int dy = 0;     //delta координат окна по Y в режиме перемещения
    int pdx = 0;    //delta размеров окна по X в режиме изменения размера
    int pdy = 0;    //delta размеров окна по Y в режиме изменения размера

    //режимы окна
    enum win_modes_enum {NO_MODE /*Нет режима*/ = -1,
                         RESIZE_MODE /*Режим - изменение размера*/,
                         MOUSE_MOVE_MODE /*Режим - перетаскивание*/ };

    win_modes_enum current_mode = win_modes_enum::NO_MODE;//текущий режим окна

    bool isResize = false;      //признак режима изменения размера
    bool isMouseMove = false;   //признак режима перемещения

signals:
    void si_hide();

public slots:
    void sl_button_close_clicked();         //нажатие кнопки - закрыть
    void sl_button_onwin_clicked();         //нажатие кнопки - весь экран/норма
    void sl_button_minimize_clicked();      //нажатие кнопки - минимизировать

    // QWidget interface
protected:
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *e);
};

#endif // BASE_WIN_H
