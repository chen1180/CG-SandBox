#pragma once
#include"graphics/api/RenderAPI.h"
#include"glm/glm.hpp"
namespace CGCore {
	class OpenGLRenderAPI: public RenderAPI
	{
	public:
		virtual void Init() override;
		virtual void Clear() override;
		virtual void ClearColor(const glm::vec4& color)override;
		// Inherited via RenderAPI
		virtual void DrawIndexed(uint32_t count, const void* start=nullptr) override;
	};
}

