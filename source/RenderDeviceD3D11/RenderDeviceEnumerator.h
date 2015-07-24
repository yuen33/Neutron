#pragma once

#include "RenderDeviceD3D11Common.h"
#include "NeutronFoundation/Array.h"

using Neutron::Container::Array;

namespace Neutron
{
	namespace System
	{
		class RenderDeviceEnumerator
		{
		public:
			struct DisplayModeInfo
			{
				int width;
				int height;
				int freshRateNumberator;
				int freshRateDenominator;

				DisplayModeInfo()
				{
				}

				DisplayModeInfo( int w, int h, int n, int d )
					: width( w )
					, height( h )
					, freshRateNumberator( n )
					, freshRateDenominator( d )
				{
				}

				DisplayModeInfo& operator=( const DisplayModeInfo& rhs )
				{
					width = rhs.width;
					height = rhs.height;
					freshRateNumberator = rhs.freshRateNumberator;
					freshRateDenominator = rhs.freshRateDenominator;
					return *this;
				}
			};

			struct OutputInfo
			{
				wchar outputName[32];
				int left;
				int right;
				int top;
				int bottom;
				Array<DisplayModeInfo> displayModes;

				OutputInfo()
				{
				}

				OutputInfo( const wchar* name, int l, int r, int t, int b )
					: left( l )
					, right( r )
					, top( t )
					, bottom( b )
				{
					lstrcpynW( outputName, name,32 );
				}

				OutputInfo& operator=( const OutputInfo& rhs )
				{
					lstrcpynW( outputName, rhs.outputName, 32 );
					left =  rhs.left;
					right = rhs.right;
					top = rhs.top;
					bottom = rhs.bottom;
					displayModes = rhs.displayModes;
					return *this;
				}
			};

			struct AdapterInfo
			{
				wchar					adapterName[128];
				int						videoMemory;
				Array<OutputInfo>		outputs;

				AdapterInfo()
				{
				}

				AdapterInfo( const wchar* name, int memory )
					: videoMemory( memory )
				{
					lstrcpynW( adapterName, name, 128 );
				}

				AdapterInfo& operator=( AdapterInfo& rhs )
				{
					lstrcpynW( adapterName, rhs.adapterName, 128 );
					videoMemory = rhs.videoMemory;
					outputs = rhs.outputs;
					return *this;
				}
			};

			Array<AdapterInfo>			adapters;
			wchar						desktopOutputName[32];
			int							desktopOutputWidth;
			int							desktopOutputHeight;

		public:
			RenderDeviceEnumerator();
			virtual ~RenderDeviceEnumerator();

			boolean enumerate();

			inline const Array<AdapterInfo>& getAdapterInfo() { return adapters; }
			inline const wchar* desktopOutpuName() const { return desktopOutputName; }
			inline int desktopWidth() const { return desktopOutputWidth; }
			inline int desktopHeight() const { return desktopOutputHeight; }
		};
	}
}