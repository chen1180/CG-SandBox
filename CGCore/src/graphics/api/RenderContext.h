#pragma once
namespace CGCore {
	class RenderContext
	{
	public:
		virtual void Init()=0;
		virtual void SwapBuffer() = 0;


	};
}

