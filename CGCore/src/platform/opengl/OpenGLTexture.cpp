#include "pch.h"
#include "OpenGLTexture.h"
#include"glad/glad.h"

namespace CGCore {
	OpenGLTexture2D::OpenGLTexture2D(const std::string& path)
	{
		int width, height, channels;
		stbi_uc* data = nullptr;
		stbi_set_flip_vertically_on_load(1);
		data = stbi_load(path.c_str(), &width, &height, &channels, 0);

		CG_CORE_ASSERT(data, "Failed to load images!");
		m_Width = width;
		m_Height = height;
		GLenum dataFormat, internalFormat;
		if (channels == 3) {
			internalFormat = GL_RGB8;
			dataFormat = GL_RGB;
		}
		else if (channels == 4) {
			internalFormat = GL_RGBA8;
			dataFormat = GL_RGBA;
		}
		CG_CORE_ASSERT(internalFormat & dataFormat, "Unsupported image format!");
		m_InternalFormat = internalFormat;
		m_DataFormat = dataFormat;
		glCreateTextures(GL_TEXTURE_2D, 1, &m_RenderID);
		glTextureStorage2D(m_RenderID, 1, internalFormat, m_Width, m_Height);

		glTextureParameteri(m_RenderID, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTextureParameteri(m_RenderID, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTextureParameteri(m_RenderID, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTextureParameteri(m_RenderID, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glGenerateMipmap(GL_TEXTURE_2D);
		glTextureSubImage2D(m_RenderID, 0, 0, 0, m_Width, m_Height, dataFormat, GL_UNSIGNED_BYTE, data);

		stbi_image_free(data);
	}
	OpenGLTexture2D::OpenGLTexture2D(uint32_t width, uint32_t height):m_Width(width),m_Height(height)
	{
		//TODO: set format of custom texture in the future
		m_InternalFormat = GL_RGBA8;
		m_DataFormat = GL_RGBA;

		glCreateTextures(GL_TEXTURE_2D, 1, &m_RenderID);
		glTextureStorage2D(m_RenderID, 1, m_InternalFormat, m_Width, m_Height);

		glTextureParameteri(m_RenderID, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTextureParameteri(m_RenderID, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTextureParameteri(m_RenderID, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTextureParameteri(m_RenderID, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	void OpenGLTexture2D::Bind(uint32_t slot )
	{
		glBindTextureUnit(slot, m_RenderID);
	}
	void OpenGLTexture2D::SetData(void* data, uint32_t size)
	{
		uint32_t channel = m_DataFormat == GL_RGBA ? 4 : 3;
		CG_CORE_ASSERT(size == m_Width * m_Height * channel, "Texture2d data size error!");
		glTextureSubImage2D(m_RenderID, 0, 0, 0, m_Width, m_Height, m_DataFormat, GL_UNSIGNED_BYTE, data);
	}
	const uint32_t& OpenGLTexture2D::GetID()
	{
		return m_RenderID;
	}
	const uint32_t& OpenGLTexture2D::GetWidth()
	{
		return m_Width;
	}
	const uint32_t& OpenGLTexture2D::GetHeight()
	{
		return m_Height;
	}
	void OpenGLTexture2D::Unbind()
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	OpenGLTextureCube::OpenGLTextureCube(const std::string& path)
	{
		int width, height, channels;
		stbi_uc* data = nullptr;
		stbi_set_flip_vertically_on_load(1);
		data = stbi_load(path.c_str(), &width, &height, &channels, 0);

		CG_CORE_ASSERT(data, "Failed to load images!");
		m_Width = width;
		m_Height = height;
		GLenum dataFormat, internalFormat;
		if (channels == 3) {
			internalFormat = GL_RGB8;
			dataFormat = GL_RGB;
		}
		else if (channels == 4) {
			internalFormat = GL_RGBA8;
			dataFormat = GL_RGBA;
		}
		CG_CORE_ASSERT(internalFormat & dataFormat, "Unsupported image format!");
		m_InternalFormat = internalFormat;
		m_DataFormat = dataFormat;
		glCreateTextures(GL_TEXTURE_2D, 1, &m_RenderID);
		glTextureStorage2D(m_RenderID, 1, internalFormat, m_Width, m_Height);

		glTextureParameteri(m_RenderID, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTextureParameteri(m_RenderID, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTextureParameteri(m_RenderID, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTextureParameteri(m_RenderID, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glGenerateMipmap(GL_TEXTURE_2D);
		glTextureSubImage2D(m_RenderID, 0, 0, 0, m_Width, m_Height, dataFormat, GL_UNSIGNED_BYTE, data);

		stbi_image_free(data);
	}
	void OpenGLTextureCube::Bind(uint32_t slot)
	{
	}
	void OpenGLTextureCube::SetData(void* data, uint32_t size)
	{
	}
	const uint32_t& OpenGLTextureCube::GetID()
	{
		// TODO: insert return statement here
		return m_RenderID;
	}
	const uint32_t& OpenGLTextureCube::GetWidth()
	{
		// TODO: insert return statement here
		return m_Width;
	}
	const uint32_t& OpenGLTextureCube::GetHeight()
	{
		// TODO: insert return statement here
		return m_Height;
	}
	void OpenGLTextureCube::Unbind()
	{
	}
}
