#include "terminal_win.h"
#include "ui_terminal_win.h"
#include <QScrollBar>

terminal_win::terminal_win(QWidget *parent) :
    Base_Dialog(parent),
    ui(new Ui::terminal_win)
{
    ui->setupUi(this);
    ui->pushButton_close->setIcon(QIcon(QString(":/images/1449324474_delete.png")));
}

terminal_win::~terminal_win()
{
    delete ui;
}

void terminal_win::sl_receive_raw_string(QString str)
{
    buffer.append(str);
    ui->textEdit_terminal->setPlainText(buffer);
    ui->textEdit_terminal->verticalScrollBar()->setValue(ui->textEdit_terminal->verticalScrollBar()->maximum());
}

void terminal_win::sl_clear_terminal()
{
    buffer.clear();
    ui->textEdit_terminal->clear();
}

void terminal_win::on_pushButton_close_clicked()
{
    emit si_hide();
}
