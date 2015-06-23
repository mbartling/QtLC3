#include "mainwindow.h"
#include <QApplication>
#include <QTextStream>
#include <QFile>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //Load the stylesheet
    QFile f(":qdarkstyle/style.qss");
    if (!f.exists())
    {
        printf("Unable to set stylesheet, file not found\n");
        }
        else
        {
            f.open(QFile::ReadOnly | QFile::Text);
            QTextStream ts(&f);
//            QApplication::instance()->setStyleSheet(ts.readAll());
            a.setStyleSheet(ts.readAll());
        }
    MainWindow w;

    w.show();

    return a.exec();
}
