#pragma once
#include"graphics/api/Texture.h"
namespace CGCore {
	class OpenGLTexture2D:public Texture2D
	{
	public:
		OpenGLTexture2D(const std::string& path);
		OpenGLTexture2D(uint32_t width,uint32_t height);
		// Inherited via Texture2D
		virtual void Bind(uint32_t slot = 0) override;

		virtual void SetData(void* data,  uint32_t size) override;

		virtual const uint32_t& GetID() override;

		virtual const uint32_t& GetWidth() override;

		virtual const uint32_t& GetHeight() override;

		virtual void Unbind() override;

		virtual bool operator==(const Texture& other) const override {
			return m_RenderID== ((OpenGLTexture2D&)other).m_RenderID;
		};
	private:
		unsigned int m_InternalFormat , m_DataFormat;
		
		uint32_t m_Width, m_Height;
		uint32_t m_RenderID;

	};
	class OpenGLTextureCube :public TextureCube
	{
	public:
		OpenGLTextureCube(const std::string& path);
		// Inherited via Texture2D
		virtual void Bind(uint32_t slot = 0) override;

		virtual void SetData(void* data, uint32_t size) override;

		virtual const uint32_t& GetID() override;

		virtual const uint32_t& GetWidth() override;

		virtual const uint32_t& GetHeight() override;

		virtual void Unbind() override;

		virtual bool operator==(const Texture& other) const override {
			return m_RenderID == ((OpenGLTextureCube&)other).m_RenderID;
		};
	private:
		unsigned int m_InternalFormat, m_DataFormat;

		uint32_t m_Width, m_Height;
		uint32_t m_RenderID;

	};
	class OpenGLDepthTexture : public DepthTexture {

	public:
		OpenGLDepthTexture(uint32_t width,uint32_t height);
		// Inherited via DepthTexture
		virtual void Bind(uint32_t slot = 0) override;

		virtual const uint32_t& GetID() override;

		virtual const uint32_t& GetWidth() override;

		virtual const uint32_t& GetHeight() override;

		virtual void Unbind() override;

		virtual bool operator==(const Texture& other) const override {
			return m_RenderID == ((OpenGLDepthTexture&)other).m_RenderID;
		};
	private:
		uint32_t m_Width, m_Height;
		uint32_t m_RenderID;

	};
}

