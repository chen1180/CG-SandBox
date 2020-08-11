#include "pch.h"
#include "RenderCommand.h"
#include"platform/opengl/OpenGLRenderAPI.h"
namespace CGCore {
	RenderAPI* RenderCommand::s_RenderAPI= new OpenGLRenderAPI();
}