#include "mainwindow.h"
#include "dropslabel.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow mainwindow;

    DropsLabel label;
    label.show();

    QObject::connect(&label, SIGNAL(signal1(QString)), &mainwindow, SLOT(open(QString)));

    return a.exec();
}
