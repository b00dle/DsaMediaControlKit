#include "preset.h"

namespace Preset {

Preset::Preset(QObject *parent)
    : QObject(parent)
    , id_iterator_(0)
    , name_("")
    , components_()
{

}

Preset::Preset(QObject *parent, QString name)
    : QObject(parent)
    , id_iterator_(0)
    , name_(name)
    , components_()
{

}


Preset::~Preset()
{

}

void Preset::startPreset(bool)
{
    emit presetStart();
}

QString Preset::name() const
{
    return name_;
}

void Preset::setName(const QString &name)
{
    name_ = name;
}

} //namespace Preset
