#include "pch.h"
#include "LayerStack.h"
namespace CGCore {
	LayerStack::~LayerStack()
	{
		for (Layer* layer:m_LayerStacks)
		{
			layer->OnDettach();
			delete layer;
		}
	}
	void LayerStack::PushLayer(Layer* layer)
	{
		m_LayerStacks.emplace(m_LayerStacks.begin()+m_Index,layer);
		m_Index++;
	}
	void LayerStack::PopLayer(Layer* layer)
	{
		auto iterator = std::find(m_LayerStacks.begin(), m_LayerStacks.end(), layer);
		if (iterator != m_LayerStacks.begin() + m_Index) {
			layer->OnDettach();
			m_LayerStacks.erase(iterator);
			m_Index--;

		}
	}
}