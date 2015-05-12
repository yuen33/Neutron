#pragma once

#include "Platform.h"

#ifdef NEUTRON_FOUNDATION_BUILD
#define NEUTRON_FOUNDATION_CORE NEUTRON_PLUGIN_EXPORT
#else
#define NEUTRON_FOUNDATION_CORE NEUTRON_PLUGIN_IMPORT
#endif

namespace Neutron
{
}