#include "pch.h"
#include "Renderer2D.h"
#include"graphics/api/RenderCommand.h"
#include"imgui.h"
namespace CGCore {
	struct Renderer2DData {
		//Render2D Batch capability
		static const uint32_t MaxQuadCount = 10000;
		static const uint32_t MaxQuadVertex = MaxQuadCount * 4;
		static const uint32_t MaxQuadIndices = MaxQuadCount * 6;
		//Each render primitive data
		QuadVertex* QuadVertexBasePtr;
		QuadVertex* QuadVertexPtr;
		uint32_t QuadIndexCount;
		Renderer2D::Statistics Stats;
		Renderer2DData() :QuadVertexBasePtr(nullptr), QuadVertexPtr(nullptr), QuadIndexCount(0) {}
		~Renderer2DData() {
			delete QuadVertexBasePtr;
			delete QuadVertexPtr;
		}

		Ref<VertexBuffer> QuadVertexBuffer;
		Ref<VertexArray> QuadVertexArray;
		Ref<Shader> TextureShader;

		glm::vec4 QuadVertices[4];
		glm::vec2 QuadTextureCoords[4];
	};

	 Renderer2DData* Renderer2D::s_RenderData=nullptr;
	void Renderer2D::Init()
	{
		s_RenderData =new Renderer2DData();
		s_RenderData->QuadVertexArray = VertexArray::Create();

		BufferLayout layout = {
			{"Position",ShaderDataType::Float3},
			{"Color",ShaderDataType::Float4},
			{"TexCoord",ShaderDataType::Float2}
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

		s_RenderData->TextureShader = Shader::Create(std::string("assets/shader/Texture.vert.glsl"), std::string("assets/shader/Texture.frag.glsl"));
		s_RenderData->TextureShader->Bind();

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
		s_RenderData->TextureShader->UploadUniformMat4("u_ViewMatrix", camera->GetViewMatrix());
		s_RenderData->TextureShader->UploadUniformMat4("u_ProjectionMatrix", camera->GetProjectionMatrix());
		
		s_RenderData->QuadIndexCount = 0;
		s_RenderData->QuadVertexPtr = s_RenderData->QuadVertexBasePtr;

		s_RenderData->QuadVertexArray->Bind();
		s_RenderData->QuadVertexArray->GetIndexBuffer()->Bind();


	}
	void Renderer2D::EndScene()
	{
		uint32_t dataSize = uint32_t((uint8_t*)s_RenderData->QuadVertexPtr - (uint8_t*)s_RenderData->QuadVertexBasePtr);
		s_RenderData->QuadVertexBuffer->SetData(s_RenderData->QuadVertexBasePtr,dataSize);
		
		Render();

	}
	void Renderer2D::Render() {
	
		RenderCommand::DrawIndexed(s_RenderData->QuadIndexCount);
		s_RenderData->Stats.DrawCalls++;
	}

	//Draw quad
	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color) {
		auto& transform = glm::translate(glm::mat4(1.0f), position) *
			glm::scale(glm::mat4(1.0f), { size.x,size.y,1.0 });

		for (int i = 0;i < 4;i++) {
			s_RenderData->QuadVertexPtr->Position = transform * s_RenderData->QuadVertices[i];
			s_RenderData->QuadVertexPtr->Color = color;
			s_RenderData->QuadVertexPtr->TexCoord = s_RenderData->QuadTextureCoords[i];
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
		ImGui::Text("Quads: %d", s_RenderData->Stats.QuadCount);
		ImGui::Text("Vertices: %d", s_RenderData->Stats.GetTotalVertexCount());
		ImGui::Text("Indices: %d", s_RenderData->Stats.GetTotalIndicesCount());
		ImGui::End();
	}
}