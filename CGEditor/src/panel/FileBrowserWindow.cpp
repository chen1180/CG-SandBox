#include "FileBrowserWindow.h"
#include "utils/StringUtils.h"

namespace CGCore {
	FileBrowserWindow::FileBrowserWindow()
	{
		m_FileBrowser = ImGui::FileBrowser(ImGuiFileBrowserFlags_CreateNewDir | ImGuiFileBrowserFlags_EnterNewFilename);
		m_FileBrowser.SetTitle("File Browser");
	}
	void FileBrowserWindow::OnImGuiRender()
	{
		m_FileBrowser.Display();

		if (m_FileBrowser.HasSelected())
		{
			std::string tempFilePath = m_FileBrowser.GetSelected().string();
			CG_CORE_INFO("Selected filename: {}", tempFilePath)
			std::string filePath = BackSlashesToSlashes(tempFilePath);

			m_Callback(filePath);
			m_FileBrowser.ClearSelected();
		}
	}
	void FileBrowserWindow::Open( const std::vector<const char*>& filter)
	{
		m_FileBrowser.SetTypeFilters(filter);
		m_FileBrowser.Open();
	}
}