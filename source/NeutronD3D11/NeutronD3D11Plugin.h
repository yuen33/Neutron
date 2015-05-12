#include "NeutronD3D11Common.h"

#include "NeutronSystem/NeutronPlugin.h"

using Neutron::System::NeutronPlugin;
using Neutron::System::NeutronDevice;

namespace Neutron
{
	class NEUTRON_D3D11_CORE NeutronD3D11Plugin : public NeutronPlugin
	{
	public:
		NeutronD3D11Plugin();
		virtual ~NeutronD3D11Plugin();

		virtual int getDeviceCount();
		virtual NeutronDevice* getDevice( int index );
	};

	extern "C"
	{
		NEUTRON_D3D11_CORE NeutronD3D11Plugin* createPlugin();
		NEUTRON_D3D11_CORE void destroyPlugin( NeutronPlugin* plugin );
	}
}