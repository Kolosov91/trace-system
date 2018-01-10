#ifndef PREFENCES_WIN_H
#define PREFENCES_WIN_H

#include <QDialog>

namespace Ui {
class prefences_win;
}

class prefences_win : public QDialog
{
    Q_OBJECT

public:
    explicit prefences_win(QWidget *parent = 0);
    ~prefences_win();

private slots:
    void on_pushButton_accept_clicked();

    void on_pushButton_cancel_clicked();

private:
    Ui::prefences_win *ui;
};

#endif // PREFENCES_WIN_H
