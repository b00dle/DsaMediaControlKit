#include "preset.h"

namespace Preset {

Preset::Preset(QObject *parent)
    : QObject(parent)
    ,name_("")
    ,id_iterator_(0)
{

}

} //namespace Preset
