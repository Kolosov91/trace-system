#ifndef INFO_ABOUT_APP_WIN_H
#define INFO_ABOUT_APP_WIN_H

#include <QWidget>
#include "base_win.h"

namespace Ui {
class info_about_app_win;
}

class info_about_app_win : public Base_Dialog
{
    Q_OBJECT

public:
    explicit info_about_app_win(QWidget *parent = 0);
    ~info_about_app_win();

private slots:
    void on_pushButton_close_clicked();

private:
    Ui::info_about_app_win *ui;
};

#endif // INFO_ABOUT_APP_WIN_H
