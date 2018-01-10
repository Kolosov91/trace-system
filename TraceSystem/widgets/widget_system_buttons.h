#ifndef WIDGET_SYSTEM_BUTTONS_H
#define WIDGET_SYSTEM_BUTTONS_H

#include <QWidget>

namespace Ui {
class widget_system_buttons;
}

//Виджет системных кнопок (нужен, когда нет стандартной системной рамки)
class widget_system_buttons : public QWidget
{
    Q_OBJECT

public:
    explicit widget_system_buttons(QWidget *parent = 0);
    ~widget_system_buttons();
    void setVisible_close_button(bool isVisible);       //Управление видимостью кнопки - закрыть
    void setVisible_onwin_button(bool isVisible);       //Управление видимостью кнопки - весь экран/норма
    void setVisible_minimize_button(bool isVisible);    //Управление видимостью кнопки - минимизировать

signals:
    void si_button_close_clicked();         //сигнал нажатие кнопки - закрыть
    void si_button_onwin_clicked();         //сигнал нажатие кнопки - весь экран/норма
    void si_button_minimize_clicked();      //сигнал нажатие кнопки - минимизировать

private slots:
    void on_pushButton_close_clicked();     //нажатие кнопки - закрыть
    void on_pushButton_onwin_clicked();     //нажатие кнопки - весь экран/норма
    void on_pushButton_minimize_clicked();  //нажатие кнопки - минимизировать

private:
    Ui::widget_system_buttons *ui;
};

//Подключение слотов-сигналов к виджету
#define CONNECT_TO_widget_system_buttons(p_signal, p_receiver) \
    connect(p_signal, SIGNAL(si_button_close_clicked()), p_receiver, SLOT(sl_button_close_clicked())); \
    connect(p_signal, SIGNAL(si_button_minimize_clicked()), p_receiver, SLOT(sl_button_minimize_clicked())); \
    connect(p_signal, SIGNAL(si_button_onwin_clicked()), p_receiver, SLOT(sl_button_onwin_clicked()));

#endif // WIDGET_SYSTEM_BUTTONS_H
