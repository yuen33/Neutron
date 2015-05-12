#pragma once

#include "NeutronFoundation/NeutronFoundationCommon.h"

#if defined NEUTRON_SYSTEM_BUILD
#define NEUTRON_CORE NEUTRON_PLUGIN_EXPORT
#else
#define NEUTRON_CORE NEUTRON_PLUGIN_IMPORT
#endif

namespace Neutron
{
}