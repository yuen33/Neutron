#include "Window.h"

namespace Neutron
{
	namespace Engine
	{
#ifdef NEUTRON_WINDOWS_DESKTOP
		LRESULT Window::wndproc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam )
		{
			Window* window = reinterpret_cast<Window*>( GetWindowLongPtrA( hWnd, GWLP_USERDATA ) );
			if( window )
			{
				return window->msgproc( hWnd, msg, wParam, lParam );
			}

			return DefWindowProcA( hWnd, msg, wParam, lParam );
		}

		LRESULT Window::msgproc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam )
		{
			switch( msg )
			{
				case WM_ACTIVATE:
				{
					boolean newActive = LOWORD( wParam ) == WA_ACTIVE;
					if( active != newActive )
					{
						onActive( newActive );
						active = newActive;
					}
				}
				break;
				
				case WM_ERASEBKGND:
				{
				}
				break;

				case WM_PAINT:
				{
					onPaint();
				}
				break;

				case WM_ENTERSIZEMOVE:
				{
					updateFlag = false;
					onEnterSizeMove();
				}
				break;

				case WM_SIZE:
				{
					boolean newActive = ( wParam != SIZE_MAXHIDE ) && ( wParam != SIZE_MINIMIZED );
					if( active != newActive )
					{
						onActive( newActive );
						active = newActive;
					}

					onSize();
				}
				break;

				case WM_EXITSIZEMOVE:
				{
					onExitSizeMove();
					updateFlag = true;
				}
				break;

				case WM_SETCURSOR:
				{
					onSetCursor();
				}
				break;

				case WM_CHAR:
				{
					onChar( static_cast<wchar>( wParam ) );
				}
				break;

				case WM_INPUT:
				{
					onRawInput( reinterpret_cast<HRAWINPUT>( lParam ) );
				}
				break;

				case WM_CLOSE:
				{
					onClose();
					return 0;
				}
				break;
				
				default:
				{
				}
			}

			return DefWindowProcA( hWnd, msg, wParam, lParam );
		}

		void Window::onActive( boolean active )
		{
		}

		void Window::onPaint()
		{
		}

		void Window::onEnterSizeMove()
		{
		}

		void Window::onSize()
		{
		}

		void Window::onExitSizeMove()
		{
		}

		void Window::onSetCursor()
		{
		}

		void Window::onChar( wchar code )
		{
			if( code == VK_ESCAPE )
			{
				release();
			}
		}

		void Window::onRawInput( HRAWINPUT rawInput )
		{
		}

		void Window::onClose()
		{
			release();
		}

		void Window::onDestroy()
		{
		}

		WindowPtr Window::create( Device* owner )
		{
			return WindowPtr( new Window( owner ) );
		}

		Window::Window( Device* owner )
			: ProcessingUnit( owner )
			, hInstance( 0 )
			, hWnd( 0 )
			, width( 0 )
			, height( 0 )
			, fullscreen( false )
			, active( false )
			, updateFlag( false )
			, done ( true )
		{
			processingUnitType = PUT_Window;
		}

		Window::~Window()
		{
			release();
		}

		boolean Window::init( int width, int height, const char* title, boolean fullscreen )
		{
			HINSTANCE instance = GetModuleHandle( 0 );

			WNDCLASSA wc;
			wc.style = 0;
			wc.lpfnWndProc = (WNDPROC)wndproc;
			wc.cbClsExtra = 0;
			wc.cbWndExtra = 0;
			wc.hInstance = instance;
			wc.hIcon = LoadIcon( 0, IDI_APPLICATION );
			wc.hCursor = LoadCursor( 0, IDC_ARROW );
			wc.hbrBackground = (HBRUSH)GetStockObject( WHITE_BRUSH );
			wc.lpszMenuName = 0;
			wc.lpszClassName = title;
			
			RegisterClassA( &wc );

			DWORD style = fullscreen ? WS_POPUP : WS_OVERLAPPEDWINDOW;
			//style &= WS_MAXIMIZEBOX;

			RECT rct;
			rct.left = 0;
			rct.right = width;
			rct.top = 0;
			rct.bottom = height;
			AdjustWindowRect( &rct, style, FALSE );

			HWND hwnd = CreateWindowA( title, title, style, 0, 0, rct.right - rct.left, rct.bottom - rct.top, 0, 0, instance, 0 );

			if( hwnd )
			{
				this->hInstance = instance;
				this->hWnd = hwnd;
				this->title = title;
				GetClientRect( hwnd, &rct );
				this->width = rct.right - rct.left;
				this->height = rct.bottom - rct.top;
				this->hInstance = instance;
				this->fullscreen = fullscreen;

				this->done = false;
				this->updateFlag = true;

				SetWindowLongPtrA( hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>( this ) );

				UpdateWindow( hwnd );
				ShowWindow( hwnd, SW_SHOW );

				return true;
			}

			UnregisterClassA( title, instance );
			return false;
		}

		void Window::release()
		{
			if( hWnd )
			{
				DestroyWindow( hWnd );
				UnregisterClassA( title.getCStr(), hInstance );
			}

			width = 0;
			height = 0;
			title.clear();
			fullscreen = false;
			active = false;
			updateFlag = false;
			done = true;
		}

		void Window::update()
		{
			MSG msg;
			if( PeekMessage( &msg, hWnd, 0, 0, PM_REMOVE ) )
			{
				TranslateMessage( &msg );
				DispatchMessage( &msg );
			}
		}

		void Window::run()
		{
			while( !done && updateFlag )
			{
				update();
			}
		}
#endif
	}
}