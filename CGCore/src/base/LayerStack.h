#pragma once
#include<vector>
#include"Layer.h"
namespace CGCore {
	class LayerStack
	{
	public:
		LayerStack() {};
		~LayerStack();

		void PushLayer(Layer* layer);
		void PopLayer(Layer* layer);

	private:
		std::vector<Layer*> m_LayerStacks;
		uint32_t m_Index=0;



	};

}
