#pragma once
#include"base/Base.h"
#include"event/Event.h"
namespace CGCore {
	class Renderer
	{
	public:
		static void Init();
		static void BeginScene();
		static void EndScene();
		static void Submit();
	};
}

