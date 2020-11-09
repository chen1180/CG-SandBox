#pragma once
#include<base/Base.h>
#include<imgui.h>
#include<plugins/fileBrowser/Imfilebrowser.h>
namespace CGCore {
	class FileBrowserWindow
	{
	public:
		FileBrowserWindow();
		~FileBrowserWindow() = default;

		void OnImGuiRender();
		void Open(const std::vector<const char*>& filter = {"*"});
		void SetCallback(const std::function<void(const std::string&)>& callback)
		{
			m_Callback = callback;
		}
	private:
		std::function<void(const std::string&)> m_Callback;
		ImGui::FileBrowser m_FileBrowser;
	};

}
