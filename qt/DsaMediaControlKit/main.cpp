#include "main_window.h"

#include <QApplication>
#include <QDebug>
#include <QTimer>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.showMaximized();

    return a.exec();
}
