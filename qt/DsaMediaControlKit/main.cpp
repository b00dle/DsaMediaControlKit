#include "main_window.h"

#include <QApplication>
#include <QDebug>
#include <QTimer>
#include "resources/resources.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Resources::init();
    a.setStyleSheet(Resources::DARK_STYLE);

    MainWindow w;
    w.showMaximized();

    int ret_code = a.exec();

    Resources::cleanup();

    return ret_code;
}
