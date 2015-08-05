#pragma once

#include "ProcessingUnit.h"
#include "NeutronFoundation/String.h"
#include "Pin.h"

#if defined NEUTRON_WINDOWS_DESKTOP
#include <dxgi.h>
#endif

using Neutron::Container::String;

namespace Neutron
{
	namespace Engine
	{
#if defined NEUTRON_WINDOWS_DESKTOP
		class NEUTRON_CORE Window : public ProcessingUnit
		{
		protected:
			static LRESULT wndproc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam );
			LRESULT msgproc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam );

			HWND					hWnd;
			HINSTANCE				hInstance;
			int						width;
			int						height;
			String					title;
			boolean					fullscreen;
			IDXGISwapChain*			swapchain;

			// control flag
			boolean					active;
			boolean					updateFlag;
			boolean					done;

		public:
			static ProcessingUnitPtr create( Device* owner );

			Window( Device* owner );
			virtual ~Window();

			virtual boolean init( int width, int height, const char* title, bool fullscreen );
			virtual void release();

			virtual void onActive( bool active );
			virtual void onPaint();
			virtual void onEnterSizeMove();
			virtual void onSize();
			virtual void onExitSizeMove();
			virtual void onSetCursor();
			virtual void onChar( wchar code );
			virtual void onRawInput( HRAWINPUT rawInput );
			virtual void onClose();
			virtual void onDestroy();

			virtual boolean updateUnit();
			virtual void update();
			virtual void swap();
			void run();
			inline void stop() { done = true; }

			inline boolean isDone() const { return done; }
			inline int getWidth() const { return width; }
			inline int getHeight() const { return height; }
			inline const char* getTitle() const { return title.getCStr(); }
			inline boolean isFullscreen() const { return fullscreen; }
			inline const void* getHandle() const { return hWnd; }
			inline void setSwapChain( IDXGISwapChain* sc ) { swapchain = sc; }
		};
#endif
	}
}