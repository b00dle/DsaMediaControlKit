#include "host.h"

#include <QHBoxLayout>

namespace Web {

Host::Host(QWidget *parent)
    : QDialog(parent)
    , label_()
{
    initWidgets();
    initLayout();
}

void Host::initWidgets()
{
    label_ = new QLabel(tr("HELLO WORLD"), this);
}

void Host::initLayout()
{
    setMinimumSize(200, 200);
    QHBoxLayout* layout = new QHBoxLayout;
    layout->addWidget(label_);

    setLayout(layout);
}

} // namespace Web
