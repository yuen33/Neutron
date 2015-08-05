#include "ProcessingUnitManager.h"
#include "NeutronFoundation/Hash.h"
#include "SystemDevice.h"
#include "RenderDevice.h"
#include "Renderer.h"
#include "ProcessingModule.h"
#include "Window.h"

namespace Neutron
{
	namespace Engine
	{
		ProcessingUnitManager::ProcessingUnitManager()
		{
		}

		ProcessingUnitManager::~ProcessingUnitManager()
		{
		}

#pragma optimize ( "", off )
		void ProcessingUnitManager::registerProcessingUnit( const char* name, int processingUnitType, Device* device )
		{
			ProcessingUnitInfo* newInfo = new ProcessingUnitInfo( processingUnitType, name, device );
			nameIndex.add( Math::Hash::DJB32( name ), newInfo );
			HashMap<int, Array<ProcessingUnitInfo*> >::Iterator itTypeIndex = typeIndex.find( processingUnitType );
			if( itTypeIndex != typeIndex.end() )
			{
				itTypeIndex.value().add( newInfo );
			}
			else
			{
				Array<ProcessingUnitInfo*> newInfoArray;
				newInfoArray.add( newInfo );
				typeIndex.add( processingUnitType, newInfoArray );
			}
		}
#pragma optimize ( "", on )

		void ProcessingUnitManager::unregisterProcessingUnit( const char* name )
		{
			// find name
			HashMap<uint32, ProcessingUnitInfo*>::Iterator itNameIndex = nameIndex.find( Math::Hash::DJB32( name ) );
			if( itNameIndex != nameIndex.end() )
			{
				// find type
				int processingUnitType = itNameIndex.value()->processingUnitType;
				HashMap<int, Array<ProcessingUnitInfo*> >::Iterator itTypeIndex= typeIndex.find( processingUnitType );
				if( itTypeIndex != typeIndex.end() )
				{
					// search array
					Array<ProcessingUnitInfo*>& infoArray = itTypeIndex.value();
					int removeIndex = -1;
					for( int i = 0; i < infoArray.getCount(); ++i )
					{
						if( infoArray[i] == itNameIndex.value() )
						{
							removeIndex = i;
							break;
						}
					}

					// remove from array
					if( removeIndex >= 0 )
					{
						infoArray.removeAtFast( removeIndex );
					}
				}

				// delete info
				delete itNameIndex.value();
				nameIndex.remove( itNameIndex );
			}
		}

#pragma optimize ( "", off )
		ProcessingUnitManager::ProcessingUnitInfo* ProcessingUnitManager::findInfoByProcessingUnitType( int processingUnitType )
		{
			HashMap<int, Array<ProcessingUnitInfo*> >::Iterator itTypeIndex = typeIndex.find( processingUnitType );
			if( itTypeIndex != typeIndex.end() )
			{
				return itTypeIndex.value()[0];
			}

			return 0;
		}
#pragma optimize ( "", on )
		ProcessingModulePtr ProcessingUnitManager::createProcessingModule()
		{
			ProcessingUnitInfo* info = findInfoByProcessingUnitType( PUT_Module );
			if( info )
			{
				System::SystemDevice* device = static_cast<System::SystemDevice*>( info->device );
				if( device )
				{
					return device->createProcessingModule();
				}
			}

			return ProcessingModulePtr::null;
		}

		Render::RendererPtr ProcessingUnitManager::createRenderer()
		{
			ProcessingUnitInfo* info = findInfoByProcessingUnitType( PUT_Renderer );
			if( info )
			{
				System::RenderDevice* device = static_cast<System::RenderDevice*>( info->device );
				if( device )
				{
					return device->createRenderer();
				}
			}

			return Render::RendererPtr::null;
		}

		WindowPtr ProcessingUnitManager::createWindow( int width, int height, const char* title, boolean fullscreen )
		{
			ProcessingUnitInfo* info = findInfoByProcessingUnitType( PUT_Window );
			if( info )
			{
				System::SystemDevice* device = static_cast<System::SystemDevice*>( info->device );
				if( device )
				{
					return device->createWindow( width, height, title, fullscreen );
				}
			}

			return WindowPtr::null;
		}
	}
}