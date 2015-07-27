#include "RenderDeviceEnumerator.h"
#include <dxgi.h>
#include "NeutronFoundation/String.h"
#include "NeutronSystem/Log.h"

using Neutron::Container::String;

namespace Neutron
{
	namespace System
	{
		RenderDeviceEnumerator::RenderDeviceEnumerator()
		{
		}

		RenderDeviceEnumerator::~RenderDeviceEnumerator()
		{
		}

		void RenderDeviceEnumerator::getDesktopOutputResolution()
		{
			// get current display mode and device
			DEVMODEW deviceMode;
			EnumDisplaySettings( 0, ENUM_CURRENT_SETTINGS, &deviceMode );
			DISPLAY_DEVICE displayDevice;
			displayDevice.cb = sizeof( displayDevice );
			boolean ret = true;
			uint32 displayDeviceIndex = 0;
			while( ret )
			{
				ret = EnumDisplayDevices( 0, displayDeviceIndex, &displayDevice, EDD_GET_DEVICE_INTERFACE_NAME ) != FALSE;
				if( ret && displayDevice.StateFlags & DISPLAY_DEVICE_ATTACHED_TO_DESKTOP )
				{
					lstrcpynW( desktopOutputName, displayDevice.DeviceName, 32 );
					desktopOutputWidth = deviceMode.dmPelsWidth;
					desktopOutputHeight = deviceMode.dmPelsHeight;
				}

				++displayDeviceIndex;
			}
		}

		void RenderDeviceEnumerator::getDesktopAdapterIndex()
		{
			for( int i = 0; i < adapters.getCount(); ++i )
			{
				AdapterInfo& adapterInfo = adapters[i];
				for( int j = 0; j < adapterInfo.outputs.getCount(); ++j )
				{
					OutputInfo& outputInfo = adapterInfo.outputs[j];
					if( lstrcmpW( outputInfo.outputName, desktopOutputName ) == 0 )
					{
						desktopAdapterIndex = i;
						return;
					}
				}
			}

			desktopAdapterIndex = -1;
		}

		boolean RenderDeviceEnumerator::enumerate()
		{
			getDesktopOutputResolution();

			IDXGIFactory* factory = 0;
			HRESULT hr = CreateDXGIFactory( __uuidof( IDXGIFactory ), (void**)&factory );
			if( FAILED( hr ) )
			{
				return false;
			}

			// enumerate adaptors
			adapters.clear();

			int numAdapters = 0;
			IDXGIAdapter* adapter = 0;
			while( factory->EnumAdapters( numAdapters, &adapter ) != DXGI_ERROR_NOT_FOUND )
			{
				DXGI_ADAPTER_DESC adapterDesc;
				adapter->GetDesc( &adapterDesc );

				adapters.add( AdapterInfo( adapterDesc.Description, adapterDesc.DedicatedVideoMemory ) );
				AdapterInfo& adpaterInfo = adapters.back();

				// enumerat outputs
				IDXGIOutput* output;
				int32 numOutputs = 0;
				while( adapter->EnumOutputs( numOutputs, &output ) != DXGI_ERROR_NOT_FOUND )
				{
					DXGI_OUTPUT_DESC outputDesc;
					output->GetDesc( &outputDesc );

					adpaterInfo.outputs.add( OutputInfo(
						outputDesc.DeviceName,
						outputDesc.DesktopCoordinates.left,
						outputDesc.DesktopCoordinates.right,
						outputDesc.DesktopCoordinates.top,
						outputDesc.DesktopCoordinates.bottom
						)
					);

					OutputInfo& outputInfo = adpaterInfo.outputs.back();

					++numOutputs;
					output->Release();
					output = 0;
				}

				++numAdapters;
				adapter->Release();
				adapter = 0;
			}

			factory->Release();

			getDesktopAdapterIndex();

			return true;
		}

		void RenderDeviceEnumerator::printDeviceInfo()
		{
			for( int i = 0; i < adapters.getCount(); ++i )
			{
				Log::message( "RenderDevice.D3D11.RenderDeviceEnumerator", String::format( "Detected adpater %ls\n", adapters[i].adapterName ).getCStr() );
			}
		}
	}
}