#pragma once

#include <cassert>
#include <cstdlib>
#include <cstdio>

#include "NeutronFoundation/Timer.h"
#include "NeutronFoundation/Memory.h"
#include "NeutronSystem/FileRenderGraph.h"
#include "NeutronSystem/RenderGraph.h"

using Neutron::System::File::FileRenderGraph;
using Neutron::Engine::Render::RenderNode;

int main(int argc, char** argv)
{
	Timer timer;
	Neutron::Memory::init();
	{
		RenderNodePtr p = FileRenderGraph::load( "../data/material/test.rendergraph");
		printf( "p is %s\n", p.isNull() ? "invalid" : "valid" );
	}
	Neutron::Memory::release();
	printf( "%f ms elapsed\n", timer.elapsedMS() );
	system( "pause" );
}