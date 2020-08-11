#pragma once
#include"base/Base.h"
#include"graphics/api/RenderAPI.h"

namespace CGCore {
	class RenderCommand
	{
	public:
		inline static void Init() {
			s_RenderAPI->Init();
		}
		inline static void Clear() {
			s_RenderAPI->Clear();
		}
		inline static void DrawIndexed(uint32_t count, const void* start = nullptr) {
			s_RenderAPI->DrawIndexed(count, start );
		}
	private:
		static RenderAPI* s_RenderAPI;
	};
}

