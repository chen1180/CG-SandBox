#pragma once
#include"graphics/RenderAPI.h"
namespace CGCore {
	class OpenGLRenderAPI: public RenderAPI
	{
	public:
		virtual void Init() override;
		virtual void Clear() override;
	};
}

