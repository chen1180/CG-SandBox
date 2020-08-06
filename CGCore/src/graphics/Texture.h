#pragma once
#include"base/Base.h"
#include"stb_image.h"
namespace CGCore {
	class Texture {
	public:
		virtual ~Texture() {};
		virtual void Bind(uint32_t slot=0) = 0;
		virtual void SetData(void* data) = 0;
		virtual const uint32_t& GetID() = 0;
		virtual const uint32_t& GetWidth() = 0;
		virtual const uint32_t& GetHeight() = 0;
		virtual void Unbind() = 0;

	};

	class Texture2D :public Texture {
	public:
		static Ref<Texture2D> Create(const std::string& path);

	};
}

