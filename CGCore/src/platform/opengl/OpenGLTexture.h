#pragma once
#include"graphics/api/Texture.h"
namespace CGCore {
	class OpenGLTexture2D:public Texture2D
	{
	public:
		OpenGLTexture2D(const std::string& path);
		// Inherited via Texture2D
		virtual void Bind(uint32_t slot = 0) override;

		virtual void SetData(void* data) override;

		virtual const uint32_t& GetID() override;

		virtual const uint32_t& GetWidth() override;

		virtual const uint32_t& GetHeight() override;

		virtual void Unbind() override;
	private:
		unsigned int m_InternalFormat , m_DataFormat;
		
		uint32_t m_Width, m_Height;
		uint32_t m_RenderID;

	};
}

