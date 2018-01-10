#ifndef TERMINAL_WIN_H
#define TERMINAL_WIN_H

#include <QWidget>
#include "base_win.h"

namespace Ui {
class terminal_win;
}

class terminal_win : public Base_Dialog
{
    Q_OBJECT

public:
    explicit terminal_win(QWidget *parent = 0);
    ~terminal_win();

public slots:
    void sl_receive_raw_string(QString str);                //Принять сырую строку
    void sl_clear_terminal();                      //очистить список точек трассировки

private slots:
    void on_pushButton_close_clicked();

private:
    Ui::terminal_win *ui;
    QString buffer;
};

#endif // TERMINAL_WIN_H
