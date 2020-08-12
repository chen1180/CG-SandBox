#pragma once
#include"base/Base.h"
#include"graphics/api/Buffer.h"
#include"graphics/api/VertexArray.h"
#include"graphics/api/Shader.h"
#include"glm/glm.hpp"
#include"glm/gtc/matrix_transform.hpp"
#include"graphics/camera/Camera.h"
namespace CGCore {
	struct QuadVertex {
		glm::vec3 Position;
		glm::vec4 Color;
		glm::vec2 TexCoord;
	};
	
	struct Renderer2DData;
	class Renderer2D
	{
	public:
		static void Init();
		static void ShutDown();
		static void BeginScene(Camera* camera);
		static void EndScene();
		//TODO: remove it. This is for testing
		static void OnImguiRender();
		//Draw quad
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color);

		struct Statistics {
			uint32_t DrawCalls = 0;
			uint32_t QuadCount = 0;

			uint32_t GetTotalVertexCount() { return QuadCount * 4; }
			uint32_t GetTotalIndicesCount() { return QuadCount * 6; }

		};
		static void Reset2DStats();
	private:
		static void Render();

	private:
		static Renderer2DData* s_RenderData;
	};
}