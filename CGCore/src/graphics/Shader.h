#pragma once
#include"base/Base.h"
#include<string>

namespace CGCore {
	class Shader
	{
	public:
		virtual ~Shader() {};
		virtual bool Compile() = 0;
		virtual void Bind() = 0;
		virtual void Unbind() = 0;
		
		static Ref<Shader>  Create(const char* vertexSource, const char* fragmentSource);
	};

}
