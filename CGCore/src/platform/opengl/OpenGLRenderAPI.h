#pragma once
#include"graphics/api/RenderAPI.h"
namespace CGCore {
	class OpenGLRenderAPI: public RenderAPI
	{
	public:
		virtual void Init() override;
		virtual void Clear() override;

		// Inherited via RenderAPI
		virtual void DrawIndexed(uint32_t count, const void* start=nullptr) override;
	};
}

