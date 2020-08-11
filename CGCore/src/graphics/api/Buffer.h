#pragma once
#include"base/Base.h"
#include"glad/glad.h"
namespace CGCore {
	enum class ShaderDataType {
		None = 0,Int,Int2,Int3,Int4,Float, Float2, Float3, Float4,Bool,Mat3,Mat4
	};
	static uint32_t ShaderDataTypeSize(ShaderDataType type) {
		switch (type)
		{
		case CGCore::ShaderDataType::Int:
			return 4;
		case CGCore::ShaderDataType::Int2:
			return 4*2;
		case CGCore::ShaderDataType::Int3:
			return 4*3;
		case CGCore::ShaderDataType::Int4:
			return 4 * 4;
		case CGCore::ShaderDataType::Float:
			return 4;
		case CGCore::ShaderDataType::Float2:
			return 4 * 2;
		case CGCore::ShaderDataType::Float3:
			return 4 * 3;
		case CGCore::ShaderDataType::Float4:
			return 4 * 4;
		case CGCore::ShaderDataType::Bool:
			return 1;
		case CGCore::ShaderDataType::Mat3:
			return 4 * 3*3;
		case CGCore::ShaderDataType::Mat4:
			return 4 * 4*4;
		}
		CG_CORE_ASSERT(false, "CGCore::ShaderDataType::Unknown!");
		return 0;
	}
	struct BufferElement {
		std::string Name;
		uint32_t Size;
		ShaderDataType Type;
		uint32_t Offset;
		bool Normalized;
		BufferElement(const std::string& name, ShaderDataType type, bool normalized=false) :Name(name),Type(type),Normalized(normalized),Offset(0),Size(ShaderDataTypeSize(type)) {
		
		}
		uint32_t GetComponentSize() const{
			switch (Type)
			{
			case CGCore::ShaderDataType::Int:
				return 1;
			case CGCore::ShaderDataType::Int2:
				return 2;
			case CGCore::ShaderDataType::Int3:
				return 3;
			case CGCore::ShaderDataType::Int4:
				return 4;
			case CGCore::ShaderDataType::Float:
				return 1;
			case CGCore::ShaderDataType::Float2:
				return 2;
			case CGCore::ShaderDataType::Float3:
				return 3;
			case CGCore::ShaderDataType::Float4:
				return 4;
			case CGCore::ShaderDataType::Bool:
				return 1;
			case CGCore::ShaderDataType::Mat3:
				return 3*3;
			case CGCore::ShaderDataType::Mat4:
				return 4*4;
			}
			CG_CORE_ASSERT(false, "CGCore::ShaderDataType::Unknown!");
			return 0;
		}
	};

	class BufferLayout {
	public:
		BufferLayout(const std::initializer_list<BufferElement>& elements):m_BufferElements(elements) {
			CalculateSizeAndOffset();
		}
		BufferLayout() {}
		inline std::vector<BufferElement>& GetElements(){ return m_BufferElements; }
		inline const std::vector<BufferElement>& GetElements()const { return m_BufferElements; }

		inline const uint32_t& GetStride() const{ return m_Stride; }

		std::vector<BufferElement>::iterator  begin() { return m_BufferElements.begin(); }
		std::vector<BufferElement>::iterator  end() { return m_BufferElements.end(); }

		std::vector<BufferElement>::const_iterator begin()const  { return m_BufferElements.begin(); }
		std::vector<BufferElement>::const_iterator  end()const  { return m_BufferElements.end(); }
	private:
		void CalculateSizeAndOffset() {
			for (auto& element : m_BufferElements) {
				element.Offset = m_Stride;
				m_Stride += element.Size;
			}
		};
	private:
		std::vector<BufferElement> m_BufferElements;
		uint32_t m_Stride=0;
	};
	class VertexBuffer
	{
	public:
		virtual ~VertexBuffer() {};
		virtual void Bind() = 0;
		virtual void Unbind() = 0;
		virtual void SetLayout(const BufferLayout& layout) = 0;
		virtual void SetData(const void* data, uint32_t size) = 0;
		virtual const BufferLayout& GetLayout() = 0;

		static Ref<VertexBuffer> Create(const void* data, uint32_t size);
			 
	};

	class IndexBuffer
	{
	public:
		virtual ~IndexBuffer() {};
		virtual void Bind() = 0;
		virtual void Unbind() = 0;
		virtual void SetData(unsigned int* data) = 0;
		virtual uint32_t GetCount() =0;

		static Ref<IndexBuffer> Create(unsigned int* data, uint32_t size);
	};

}
