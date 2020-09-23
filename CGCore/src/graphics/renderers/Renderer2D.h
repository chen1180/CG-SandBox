#pragma once
#include"base/Base.h"
#include"graphics/api/Buffer.h"
#include"graphics/api/VertexArray.h"
#include"graphics/api/Shader.h"
#include"graphics/api/RenderCommand.h"
#include"graphics/api/Texture.h"

#include"graphics/camera/Camera.h"

#include"glm/glm.hpp"
#include"glm/gtc/matrix_transform.hpp"

namespace CGCore {

	struct QuadVertex;
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
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size,Ref<Texture> texture, const glm::vec4& tintColor=glm::vec4(1.0f));
		struct Statistics {
			uint32_t DrawCalls = 0;
			uint32_t QuadCount = 0;

			uint32_t GetTotalVertexCount() { return QuadCount * 4; }
			uint32_t GetTotalIndicesCount() { return QuadCount * 6; }

		};
		static void Reset2DStats();
	private:
		static void Flush();
		static void FlushAndReset();
	private:
		static Renderer2DData* s_RenderData;
	};
}