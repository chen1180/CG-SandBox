#include "pch.h"
#include "Renderer2D.h"
#include"imgui.h"

namespace CGCore {
	struct QuadVertex{
		glm::vec3 Position;
		glm::vec4 Color;
		glm::vec2 TexCoord;
		float TextureIndex;
	};
	struct Renderer2DData {
		//Render2D Batch capability
		static const uint32_t MaxQuadCount = 10000;
		static const uint32_t MaxQuadVertex = MaxQuadCount * 4;
		static const uint32_t MaxQuadIndices = MaxQuadCount * 6;
		static const uint32_t MaxTextureSlot = 32; //TODO: use Opengl function to find the maximum texture capacity 
		//Each render primitive data
		QuadVertex* QuadVertexBasePtr;
		QuadVertex* QuadVertexPtr;
		uint32_t QuadIndexCount;
		Renderer2D::Statistics Stats;

		//Texture
		Ref<Texture> WhiteTexture;//Default texture
		std::array<Ref<Texture>, MaxTextureSlot> TextureSlots;
		uint32_t TextureSlotIndex = 0;
		
		Ref<VertexBuffer> QuadVertexBuffer;
		Ref<VertexArray> QuadVertexArray;
		Ref<Shader> TextureShader;
		glm::vec4 QuadVertices[4];
		glm::vec2 QuadTextureCoords[4];

		Renderer2DData() :QuadVertexBasePtr(nullptr), QuadVertexPtr(nullptr), QuadIndexCount(0) {}
		~Renderer2DData() {
			delete QuadVertexBasePtr;
			delete QuadVertexPtr;
		}
	};

	Renderer2DData* Renderer2D::s_RenderData=nullptr;
	void Renderer2D::Init()
	{
		s_RenderData =new Renderer2DData();
		s_RenderData->QuadVertexArray = VertexArray::Create();

		BufferLayout layout = {
			{"Position",ShaderDataType::Float3},
			{"Color",ShaderDataType::Float4},
			{"TexCoord",ShaderDataType::Float2},
			{"TextureIndex",ShaderDataType::Float}
		};

		s_RenderData->QuadVertexBuffer = VertexBuffer::Create(sizeof(QuadVertex)*s_RenderData->MaxQuadVertex);
		s_RenderData->QuadVertexBuffer->SetLayout(layout);
		s_RenderData->QuadVertexArray->AddVertexBuffer(s_RenderData->QuadVertexBuffer);

		uint32_t offset=0;
		uint32_t* quadIndices=new uint32_t[s_RenderData->MaxQuadIndices];
		for (uint32_t i = 0;i < s_RenderData->MaxQuadIndices;i+=6) {
			quadIndices[i + 0] = offset + 0;
			quadIndices[i + 1] = offset + 1;
			quadIndices[i + 2] = offset + 2;
			quadIndices[i + 3] = offset + 0;
			quadIndices[i + 4] = offset + 2;
			quadIndices[i + 5] = offset + 3;
			offset += 4;
		}
		Ref<IndexBuffer> m_IndexBuffer = IndexBuffer::Create(quadIndices, s_RenderData->MaxQuadIndices*sizeof(uint32_t));
		s_RenderData->QuadVertexArray->SetIndexBuffer(m_IndexBuffer);
		delete[] quadIndices;

		s_RenderData->TextureShader = Shader::Create(std::string("../assets/shader/Texture.vert.glsl"), std::string("../assets/shader/Texture.frag.glsl"));
		s_RenderData->TextureShader->Bind();
		//Texture
		int samplers[s_RenderData->MaxTextureSlot];
		for (int i = 0;i < s_RenderData->MaxTextureSlot;i++)
			samplers[i] = i;
		s_RenderData->TextureShader->UploadUniformIntArray("u_Texture", samplers, s_RenderData->MaxTextureSlot);
		
		uint32_t whiteTextureData=0xffffffff;//ff: 2^8 RGBA =8 8 8 8
		s_RenderData->WhiteTexture = Texture2D::Create(1,1);
		s_RenderData->WhiteTexture->SetData(&whiteTextureData, sizeof(whiteTextureData));
		s_RenderData->TextureSlots[0] = s_RenderData->WhiteTexture;//bind default texture
		s_RenderData->TextureSlotIndex++;
 
		s_RenderData->QuadVertexBasePtr = new QuadVertex[s_RenderData->MaxQuadVertex];
		s_RenderData->QuadVertices[0] = { -0.5f,-0.5f,0.0f,1.0f };
		s_RenderData->QuadVertices[1] = { 0.5f,-0.5f,0.0f,1.0f };
		s_RenderData->QuadVertices[2] = { 0.5f,0.5f,0.0f,1.0f };
		s_RenderData->QuadVertices[3] = { -0.5f,0.5f,0.0f,1.0f };

		s_RenderData->QuadTextureCoords[0] = { 0.0f,0.0f };
		s_RenderData->QuadTextureCoords[1] = { 1.0f,0.0f };
		s_RenderData->QuadTextureCoords[2] = { 1.0f,1.0f };
		s_RenderData->QuadTextureCoords[3] = { 0.0f,1.0f };
	}
	void Renderer2D::ShutDown()
	{
		delete s_RenderData;
	}
	void Renderer2D::BeginScene(Camera* camera)
	{
		s_RenderData->TextureShader->Bind();
		s_RenderData->TextureShader->UploadUniformMat4("uView", camera->GetViewMatrix());
		s_RenderData->TextureShader->UploadUniformMat4("uProjection", camera->GetProjectionMatrix());
		
		s_RenderData->QuadIndexCount = 0;
		s_RenderData->QuadVertexPtr = s_RenderData->QuadVertexBasePtr;

		s_RenderData->QuadVertexArray->Bind();
		s_RenderData->QuadVertexArray->GetIndexBuffer()->Bind();


	}
	void Renderer2D::EndScene()
	{
		uint32_t dataSize = uint32_t((uint8_t*)s_RenderData->QuadVertexPtr - (uint8_t*)s_RenderData->QuadVertexBasePtr);
		s_RenderData->QuadVertexBuffer->SetData(s_RenderData->QuadVertexBasePtr,dataSize);
		
		Flush();
	}
	void Renderer2D::Flush() {
	
		for (unsigned int i = 0;i < s_RenderData->TextureSlotIndex;i++) {
			s_RenderData->TextureSlots[i]->Bind(i);
		}
		RenderCommand::DrawIndexed(s_RenderData->QuadIndexCount);
		s_RenderData->Stats.DrawCalls++;
	}
	void Renderer2D::FlushAndReset() {
		EndScene();

		s_RenderData->QuadIndexCount = 0;
		s_RenderData->QuadVertexPtr = s_RenderData->QuadVertexBasePtr;
	}

	//Draw quad
	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color) {
		if (s_RenderData->QuadIndexCount >= s_RenderData->MaxQuadIndices)
			FlushAndReset();
		auto& transform = glm::translate(glm::mat4(1.0f), position) *
			glm::scale(glm::mat4(1.0f), { size.x,size.y,1.0 });
		
		float textureIndex = 0.0f;

		for (int i = 0;i < 4;i++) {
			s_RenderData->QuadVertexPtr->Position = transform * s_RenderData->QuadVertices[i];
			s_RenderData->QuadVertexPtr->Color = color;
			s_RenderData->QuadVertexPtr->TexCoord = s_RenderData->QuadTextureCoords[i];
			s_RenderData->QuadVertexPtr->TextureIndex = textureIndex;
			s_RenderData->QuadVertexPtr++;
		}

		s_RenderData->QuadIndexCount += 6;
		s_RenderData->Stats.QuadCount++;
	}
	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, Ref<Texture> texture, const glm::vec4& tintColor)
	{
		if (s_RenderData->QuadIndexCount >= s_RenderData->MaxQuadIndices)
			FlushAndReset();
		auto& transform = glm::translate(glm::mat4(1.0f), position) *
			glm::scale(glm::mat4(1.0f), { size.x,size.y,1.0 });

		float textureIndex = 0.0f;
		//check if texture exists in the current texture slots 
		for (int i = 0;i < s_RenderData->MaxTextureSlot;i++) {
			if (texture == s_RenderData->TextureSlots[i])
				textureIndex = float(i);
		}
		//If a new texture is binded, add it to texture slots
		if (textureIndex == 0.0f) {
			textureIndex = (float)s_RenderData->TextureSlotIndex;
			s_RenderData->TextureSlots[s_RenderData->TextureSlotIndex] = texture;
			s_RenderData->TextureSlotIndex++;

		}

		for (int i = 0;i < 4;i++) {
			s_RenderData->QuadVertexPtr->Position = transform * s_RenderData->QuadVertices[i];
			s_RenderData->QuadVertexPtr->Color = tintColor;
			s_RenderData->QuadVertexPtr->TexCoord = s_RenderData->QuadTextureCoords[i];
			s_RenderData->QuadVertexPtr->TextureIndex = textureIndex;
			s_RenderData->QuadVertexPtr++;
		}

		s_RenderData->QuadIndexCount += 6;
		s_RenderData->Stats.QuadCount++;

	}
	void Renderer2D::Reset2DStats() {
		memset(&s_RenderData->Stats, 0, sizeof(Renderer2D::Statistics));
	}
	void Renderer2D::OnImguiRender() {
		ImGui::Begin("Renderer2D stats:");
		ImGui::Text("DrawCalls: %d", s_RenderData->Stats.DrawCalls);
		ImGui::Text("Texture: %d", s_RenderData->TextureSlotIndex);
		ImGui::Text("Quads: %d", s_RenderData->Stats.QuadCount);
		ImGui::Text("Vertices: %d", s_RenderData->Stats.GetTotalVertexCount());
		ImGui::Text("Indices: %d", s_RenderData->Stats.GetTotalIndicesCount());
		ImGui::End();
	}
}