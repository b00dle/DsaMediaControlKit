#include "preset.h"

namespace PRE {

Preset::Preset(QObject *parent)
    : QObject(parent)
    ,name_("")
    ,id_iterator_(0)
{

}

Preset::~Preset()
{

}

} //namespace Preset
