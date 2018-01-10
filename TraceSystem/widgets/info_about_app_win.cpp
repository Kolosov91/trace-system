#include "info_about_app_win.h"
#include "ui_info_about_app_win.h"

extern QString EXP_VER;
extern QString EXP_NAME_PROG;

static QString About;

info_about_app_win::info_about_app_win(QWidget *parent) :
    Base_Dialog(parent),
    ui(new Ui::info_about_app_win)
{
    About =
    "Данное ПО является инструментом динамической трассировки программ по исходкому коду на языке С.\nАдаптировано для получения трассировочной информации по COM-порту.";

    ui->setupUi(this);
    this->setWindowFlag(Qt::Dialog, true);
    this->setWindowModality(Qt::WindowModal);
    ui->pushButton_close->setIcon(QIcon(QString(":/images/1449324474_delete.png")));
    QString text = QString("Название: %1\n\nВерсия: %2\n\nАвтор: %3\n\nНазначение:\n%4")
            .arg(EXP_NAME_PROG).arg(EXP_VER).arg("Колосов В.В.")
            .arg(About);
    ui->label_text->setText(text);
}

info_about_app_win::~info_about_app_win()
{
    delete ui;
}

void info_about_app_win::on_pushButton_close_clicked()
{
    this->close();
}
