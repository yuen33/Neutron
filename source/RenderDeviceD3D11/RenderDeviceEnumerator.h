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
				Size					videoMemory;
				Array<OutputInfo>		outputs;

				AdapterInfo()
				{
				}

				AdapterInfo( const wchar* name, Size memory )
					: videoMemory( memory )
				{
					lstrcpynW( adapterName, name, 128 );
				}

				AdapterInfo& operator=( const AdapterInfo& rhs )
				{
					lstrcpynW( adapterName, rhs.adapterName, 128 );
					videoMemory = rhs.videoMemory;
					outputs = rhs.outputs;
					return *this;
				}
			};

		private:
			Array<AdapterInfo>			adapters;
			wchar						desktopOutputName[32];
			int							desktopOutputWidth;
			int							desktopOutputHeight;
			int							desktopAdapterIndex;

			void getDesktopOutputResolution();
			void getDesktopAdapterIndex();

		public:
			RenderDeviceEnumerator();
			virtual ~RenderDeviceEnumerator();

			boolean enumerate();
			void printDeviceInfo();

			inline const Array<AdapterInfo>& getAdapterInfo() { return adapters; }
			inline const wchar* getDesktopOutpuName() const { return desktopOutputName; }
			inline int getDesktopWidth() const { return desktopOutputWidth; }
			inline int getDesktopHeight() const { return desktopOutputHeight; }
			inline int getDesktopAdapterIndex() const { return desktopAdapterIndex; }
		};
	}
}