#include "main_window.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    kit_ = new DsaMediaControlKit(this);

    setCentralWidget(kit_);
}

MainWindow::~MainWindow()
{

}
