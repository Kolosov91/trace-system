#include "widget_system_buttons.h"
#include "ui_widget_system_buttons.h"

widget_system_buttons::widget_system_buttons(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::widget_system_buttons)
{
    ui->setupUi(this);
    ui->pushButton_close->setIcon(QIcon(QString(":/images/1449324474_delete.png")));
    ui->pushButton_onwin->setIcon(QIcon(QString(":/images/1449324363_unchecked_checkbox.png")));
    ui->pushButton_minimize->setIcon(QIcon(QString(":/images/1449324943_minimize.png")));
}

widget_system_buttons::~widget_system_buttons()
{
    delete ui;
}

void widget_system_buttons::setVisible_close_button(bool isVisible)
{
    ui->pushButton_close->setVisible(isVisible);
}

void widget_system_buttons::setVisible_onwin_button(bool isVisible)
{
    ui->pushButton_onwin->setVisible(isVisible);
}

void widget_system_buttons::setVisible_minimize_button(bool isVisible)
{
    ui->pushButton_minimize->setVisible(isVisible);
}

void widget_system_buttons::on_pushButton_close_clicked()
{
    emit si_button_close_clicked();
}

void widget_system_buttons::on_pushButton_onwin_clicked()
{
    static bool winstate = false;
    if (winstate)
       ui->pushButton_onwin->setIcon(QIcon(QString(":/images/1449324363_unchecked_checkbox.png")));
    else
       ui->pushButton_onwin->setIcon(QIcon(QString(":/images/1449325122_restore_window.png")));
    winstate = !winstate;
    emit si_button_onwin_clicked();
}

void widget_system_buttons::on_pushButton_minimize_clicked()
{
    emit si_button_minimize_clicked();
}
