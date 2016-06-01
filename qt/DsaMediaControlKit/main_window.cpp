#include "main_window.h"

#include <QMenuBar>
#include <QStatusBar>
#include <QProgressBar>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , kit_(0)
{
    kit_ = new DsaMediaControlKit("Ambiente", this);

    menuBar()->addActions(kit_->getMenu()->actions());
    statusBar()->addWidget(kit_->getProgressBar(), 1);

    setCentralWidget(kit_);
}

MainWindow::~MainWindow()
{}
