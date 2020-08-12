#pragma once
#include"glm/glm.hpp"
namespace CGCore {
	class RenderAPI
	{
	public:
		enum API {
			OpenGL = 0,
			DirectX,
			Vulkan
		};
	public:
		virtual void Init()=0;
		virtual void DrawIndexed(uint32_t count, const void* = nullptr) = 0;
		virtual void ClearColor(const glm::vec4& color)=0;
		virtual void Clear() = 0;
		static API& Get() { return s_RenderAPI; }
	private:
		static API s_RenderAPI;

	};
}

