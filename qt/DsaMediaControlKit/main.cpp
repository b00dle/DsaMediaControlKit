#include "main_window.h"

#include <QApplication>
#include <QDebug>
#include <QTimer>
#include "resources/lib.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Resources::Lib::init();
    a.setStyleSheet(Resources::Lib::DARK_STYLE);

    MainWindow w;
    w.showMaximized();

    int ret_code = a.exec();

    Resources::Lib::cleanup();

    return ret_code;
}
