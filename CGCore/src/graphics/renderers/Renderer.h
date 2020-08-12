#pragma once
#include"base/Base.h"
#include"event/Event.h"
namespace CGCore {
	class Renderer
	{
	public:
		static void Init();
		static void BeginScene();
		static void DrawIndexed(uint32_t count, const void* start = nullptr);
		static void EndScene();
		static void Submit();
	};
}

