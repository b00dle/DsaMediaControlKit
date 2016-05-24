#include "main_window.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , kit_(0)
{
    kit_ = new DsaMediaControlKit("Ambiente", this);

    setCentralWidget(kit_);
}

MainWindow::~MainWindow()
{

}
