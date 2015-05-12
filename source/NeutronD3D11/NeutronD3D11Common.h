#pragma once

#include "NeutronSystem/NeutronSystemCommon.h"

#if defined NEUTRON_D3D11_BUILD
#define NEUTRON_D3D11_CORE NEUTRON_PLUGIN_EXPORT
#else 
#define NEUTRON_D3D11_CORE NEUTRON_PLUGIN_IMPORT
#endif

namespace Neutron
{
}