#pragma once
#include"base/Base.h"
#include"graphics/api/RenderAPI.h"
#include"glm/glm.hpp"
#include"glm/gtc/type_ptr.hpp"
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
		inline static void ClearColor(const glm::vec4& color=glm::vec4(0.8,0.5,0.6,1.0)) {
			s_RenderAPI->ClearColor(color);
		}
		inline static void DrawIndexed(uint32_t count, const void* start = nullptr) {
			s_RenderAPI->DrawIndexed(count, start );
		}
		inline static void OnWindowResize(uint32_t width, uint32_t height) {
			s_RenderAPI->OnWindowResize(width, height);
		}
	private:
		static RenderAPI* s_RenderAPI;
	};
}

