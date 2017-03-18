#include "main_window.h"

#include <QApplication>
#include <QDebug>
#include <QTimer>
#include <QSettings>
#include "resources/resources.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Resources::init();
    a.setStyleSheet(Resources::DARK_STYLE);
    QSettings* listener_settings = new QSettings(
        "../MyFirstWebApp/etc/webapp1.ini",
        QSettings::IniFormat,
        &a
    );

    MainWindow w;
    w.showMaximized();

    int ret_code = a.exec();

    Resources::cleanup();

    return ret_code;
}
