#pragma once
#include"base/Base.h"
#include<string>
#include"glm/glm.hpp"

namespace CGCore {
	class Shader
	{
	public:
		virtual ~Shader() {};
		virtual bool Compile() = 0;
		virtual void Bind() = 0;
		virtual void Unbind() = 0;
		virtual uint32_t GetHandle() = 0;
		
		static Ref<Shader>  Create(const char* vertexSource, const char* fragmentSource);
		static Ref<Shader>  Create(const std::string& vertexSourceFile, const  std::string& fragmentSourceFile);
	public:
		virtual void UploadUniformFloat(const std::string& name, const float& value) =0;
		virtual void UploadUniformFloat2(const std::string& name, const glm::vec2& value) =0;
		virtual void UploadUniformFloat3(const std::string& name, const glm::vec3& value)=0;

		virtual void UploadUniformInt(const std::string& name, const uint32_t& value) = 0;
		virtual void UploadUniformIntArray(const std::string& name , int* value, int count) = 0;

		virtual void UploadUniformMat2(const std::string& name, const glm::mat2& value) = 0;
		virtual void UploadUniformMat3(const std::string& name, const glm::mat3& value) = 0;
		virtual void UploadUniformMat4(const std::string& name, const  glm::mat4& value) = 0;
	};

}
