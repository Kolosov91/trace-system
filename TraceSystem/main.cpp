#include "widgets/main_win.h"
#include <QApplication>
#include <QtWidgets>
#include <QMessageBox>
#include <QFile>
#include <QSplashScreen>
#include <QLockFile>
#include <QDir>

const QString VERSION = "17.10.17";
const QString NAME_PROG = "Среда трассировки";

QString EXP_VER = VERSION;
QString EXP_NAME_PROG = NAME_PROG;



QSplashScreen* splash = NULL;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

//// Необходимо для самодостаточности запуска и работы ПО
    QStringList paths = QCoreApplication::libraryPaths();
    paths.append(".");
    paths.append("imageformats");
    paths.append("platforms");
    paths.append("sqldrivers");
    QCoreApplication::setLibraryPaths(paths);
////-----------------------------------------------------

////Проверка на один экземпляр
    QLockFile lockFile(QDir::temp().absoluteFilePath("TraceSystemApplication.lock"));
    if (!lockFile.tryLock(100))
    {
        QMessageBox msg;
        msg.setIcon(QMessageBox::Warning);
        msg.setWindowTitle("Внимание!");
        msg.setText(QString("Данное приложение уже запущено!\nРазрешено запускать только ОДИН экземпляр бесплатной версии приложения!"));
        msg.exec();
        return 1;
    }
////--------------------------

////Применение стилей
    QFile fileStyle(":/default.css");
    if (!fileStyle.exists())
    {
        QMessageBox msg;
        msg.setIcon(QMessageBox::Warning);
        msg.setWindowTitle("Внимание!");
        msg.setText(QString("Не найден стиль!"));
        msg.exec();
        return 1;
    }
    fileStyle.open(QFile::ReadOnly);
    QString strQss = QLatin1String(fileStyle.readAll());
    a.setStyleSheet(strQss);
////-----------------

////ЗАПУСК ГЛАВНОГО ОКНА
    Main_Win w;
    splash = new QSplashScreen(&w);
    w.set_TitleOfProgram(NAME_PROG, VERSION);
    w.show();
    return a.exec();
////--------------------
}
