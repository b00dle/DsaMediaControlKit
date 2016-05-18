#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QMainWindow>

#include "dsa_media_control_kit.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    QVBoxLayout widget_layout_;
    DsaMediaControlKit* kit_;
    DsaMediaControlKit* kit2_;
};

#endif // MAIN_WINDOW_H
