#pragma once
#include"CGCore.h"
#include "panel/SceneHierarchyPanel.h"
#include"panel/FileBrowserWindow.h"
namespace CGCore {

#define BIND_FILEBROWSER_FN(fn) [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }


    class EditorLayer :public Layer
    {
	public:
		EditorLayer():Layer("Example: Hello square") {}
		virtual void OnUpdate(float deltaTime) override;
		virtual void OnImGuiRender() override;
		virtual void OnAttach() override;
		virtual void OnDettach() override;
		virtual void OnEvent(Event& e) override;
		void FileOpenCallback(const std::string& filePath);
		void FileSaveCallback(const std::string& filePath);
	private:
		Ref<Shader> m_Shader,m_DepthShader;
		Ref<Camera> m_Camera;
		Ref<Texture2D> m_TextureCheckerBoard,m_TexturePig;
		bool m_ShowImguiDemo = false;
		PhongRenderer m_PhongRenderer;
		Ref<Scene> m_Scene;
		Scope<SceneHierarchyPanel> m_ScenePanel;
		Scope<FileBrowserWindow> m_FileBrowser;
		float framerate = 0.0f;
		Entity m_Light;
		
    }; 

}