#include "main_window.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , kit_(0)
{
    kit_ = new DsaMediaControlKit("Ambiente", this);
    //kit2_ = new DsaMediaControlKit(QString::fromStdString("Musik"), this);

    setCentralWidget(kit_);
    //splitDockWidget(kit_, kit2_, Qt::Horizontal );
}

MainWindow::~MainWindow()
{

}
