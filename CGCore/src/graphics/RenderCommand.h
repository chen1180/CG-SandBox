#pragma once
#include"base/Base.h"
#include"graphics/RenderAPI.h"

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
	private:
		static RenderAPI* s_RenderAPI;
	};
}

