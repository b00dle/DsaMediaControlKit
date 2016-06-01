#include "preset.h"

namespace Preset {

Preset::Preset(QObject *parent)
    : QObject(parent)
    , id_iterator_(0)
    , name_("")
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

} //namespace Preset
