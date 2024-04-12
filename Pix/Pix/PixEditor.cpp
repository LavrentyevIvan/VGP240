//====================================================================================================
// Filename:	PixEditor.h
// Created by:	Peter Chan
//====================================================================================================

#include "PixEditor.h"

#include "CommandDictionary.h"
#include "Graphics.h"
#include "VariableCache.h"
#include "Viewport.h"
#include <ImGui/Inc/imgui.h>

namespace
{
	const char* const sPixFileExtension = "pix";
	const char* const sFileDialogFilters = "Pix Files (*.pix)\0*.pix;\0All Files (*.*)\0*.*;\0";
	const uint32_t sDefaultRenderViewWidth = 500;
	const uint32_t sDefaultRenderViewHeight = 500;
	const uint32_t sDefaultPixelSize = 1;

	const TextEditor::Palette& GetPixScriptPalette()
	{
		// ABGR
		const static TextEditor::Palette p = { {
				0xff7f7f7f,	// Default
				0xffd69c56,	// Keyword
				0xff00ff00,	// Number
				0xff7070e0,	// String
				0xff70a0e0, // Char literal
				0xffffffff, // Punctuation
				0xff408080,	// Preprocessor
				0xffaaaaaa, // Identifier
				0xff9bc64d, // Known identifier
				0xffc040a0, // Preproc identifier
				0xff60c660, // Comment (single line)
				0xff60c660, // Comment (multi line)
				0xff101010, // Background
				0xffe0e0e0, // Cursor
				0x80a06020, // Selection
				0x800020ff, // ErrorMarker
				0x40f08000, // Breakpoint
				0xff707000, // Line number
				0x40000000, // Current line fill
				0x40808080, // Current line fill (inactive)
				0x40a0a0a0, // Current line edge
			} };
		return p;
	}
}

void PixEditor::Initialize()
{
	// Enable render to texture
	X::InitRenderTexture(sDefaultRenderViewWidth, sDefaultRenderViewHeight, sDefaultPixelSize);

	// Initialize language definition
	mLanguageDefinition = CommandDictionary::Get()->GenerateLanguageDefinition();

	// Load logo texture
	mLogo = X::LoadTexture("pix.png");
	mLogoAbout = X::LoadTexture("pix_about.png");

	// Disable imgui.ini
	ImGuiIO& io = ImGui::GetIO();
	io.IniFilename = nullptr;
}

void PixEditor::Terminate()
{
}

bool PixEditor::Run(float deltaTime)
{
	ShowMenuBar();
	ShowMainWindowWithDockSpace();
	ShowLogo();

	mHasDockedWindow = false;

	// Check hotkeys
	const ImGuiIO& io = ImGui::GetIO();
	if (ImGui::IsKeyPressed(VK_F5))
		Run();
	if (io.KeyCtrl)
	{
		if (ImGui::IsKeyPressed('S', false))
		{
			if (io.KeyShift)
				SaveAs();
			else
				Save();
		}
	}

	ShowScriptFileWindows();

	if (mShowRenderView)
	{
		ShowRenderView(deltaTime);
		VariableCache::Get()->ShowEditor();
	}

	if (mShowCloseConfirmationDialog)
		ShowCloseConfirmationDialog();

	if (mShowAboutDialog)
		ShowAboutDialog();

	return mRequestQuit;
}

void PixEditor::ShowMenuBar()
{
	if (ImGui::BeginMainMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			ShowFileMenu();
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Edit"))
		{
			ShowEditMenu();
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("View"))
		{
			ShowViewMenu();
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Help"))
		{
			ShowHelpMenu();
			ImGui::EndMenu();
		}
		ImGui::EndMainMenuBar();
	}
}

void PixEditor::ShowFileMenu()
{
	if (ImGui::MenuItem("New"))
		New();
	if (ImGui::MenuItem("Open", "Ctrl+O"))
		Open();
	if (ImGui::MenuItem("Save", "Ctrl+S"))
		Save();
	if (ImGui::MenuItem("Save As..", "Ctrl+Shift+S"))
		SaveAs();

	ImGui::Separator();

	if (ImGui::MenuItem("Quit", "Alt+F4"))
		mRequestQuit = true;
}

void PixEditor::ShowEditMenu()
{
	if (ImGui::MenuItem("Undo      ", "CTRL+Z"))
	{
	}
	if (ImGui::MenuItem("Redo      ", "CTRL+Y", false, false))
	{
	}
	ImGui::Separator();
	if (ImGui::MenuItem("Cut       ", "CTRL+X"))
	{
	}
	if (ImGui::MenuItem("Copy      ", "CTRL+C"))
	{
	}
	if (ImGui::MenuItem("Paste     ", "CTRL+V"))
	{
	}
}

void PixEditor::ShowViewMenu()
{
	if (ImGui::MenuItem("Render View", "F5"))
		mShowRenderView = true;
}

void PixEditor::ShowHelpMenu()
{
	if (ImGui::MenuItem("About"))
		mShowAboutDialog = true;
}

void PixEditor::ShowMainWindowWithDockSpace()
{
	ImGuiViewport* viewport = ImGui::GetMainViewport();
	ImGui::SetNextWindowPos(viewport->Pos);
	ImGui::SetNextWindowSize(viewport->Size);
	ImGui::SetNextWindowViewport(viewport->ID);

	const ImGuiWindowFlags windowFlags =
		ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking |
		ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse |
		ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove |
		ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;

	ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));

	ImGui::Begin("MainWindow", nullptr, windowFlags);
	ImGui::DockSpace(ImGui::GetID("MyDockSpace"), ImVec2(0.0f, 0.0f), ImGuiDockNodeFlags_None);
	ImGui::End();

	ImGui::PopStyleVar(3);
}

void PixEditor::ShowLogo()
{
	// Don't show logo when we have docked window as it currently does not sort properly
	if (mHasDockedWindow)
		return;

	ImGuiViewport* viewport = ImGui::GetMainViewport();
	auto io = ImGui::GetIO();
	ImVec2 window_pos = { viewport->Pos.x + viewport->Size.x * 0.5f, viewport->Pos.y + viewport->Size.y * 0.5f };
	ImVec2 window_pos_pivot = { 0.5f, 0.5f };
	ImGui::SetNextWindowPos(window_pos, ImGuiCond_Always, window_pos_pivot);
	ImGui::SetNextWindowViewport(viewport->ID);
	ImGui::SetNextWindowBgAlpha(0.1f);

	const ImGuiWindowFlags windowFlags =
		ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoDecoration |
		ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings |
		ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoNav |
		ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoMouseInputs;

	ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));

	ImGui::Begin("Logo", nullptr, windowFlags);
	ImGui::Image(
		X::GetSprite(mLogo),
		{ (float)X::GetSpriteWidth(mLogo), (float)X::GetSpriteHeight(mLogo) },
		{ 0.0f, 0.0f },
		{ 1.0f, 1.0f },
		{ 1.0f, 1.0f, 1.0f, 0.1f });
	ImGui::End();

	ImGui::PopStyleVar(2);
}

void PixEditor::ShowScriptFileWindows()
{
	auto closeIter = mScriptFiles.end();

	for (auto iter = mScriptFiles.begin(); iter != mScriptFiles.end(); ++iter)
	{
		auto& textWindow = (*iter);

		std::string filename =
			textWindow.filePath.has_filename()
			? textWindow.filePath.filename().u8string()
			: "New " + textWindow.windowId;
		std::string fileLabel = filename;
		if (textWindow.needSave)
			fileLabel += "*";

		std::string id = fileLabel + "###" + textWindow.windowId;
		ImGui::SetNextWindowSize({ 500.0f, 600.0f }, ImGuiCond_FirstUseEver);
		ImGui::SetNextWindowPos({ mNextWindowPosX, mNextWindowPosY }, ImGuiCond_FirstUseEver);

		bool open = true;
		ImGui::Begin(id.c_str(), &open);
		if (ImGui::Button("Run (F5)"))
			Run(&textWindow.editor);

		textWindow.editor.Render(filename.c_str());
		textWindow.needSave |= textWindow.editor.IsTextChanged();

		mHasDockedWindow = ImGui::IsWindowDocked();

		if (ImGui::IsWindowFocused(ImGuiFocusedFlags_ChildWindows))
			mLastFocusedScriptWindowId = textWindow.windowId;

		ImGui::End();

		if (!open)
			closeIter = iter;
	}

	// Check if close button is clicked
	if (closeIter != mScriptFiles.end())
	{
		// Check if we need to save
		if (closeIter->needSave)
		{
			mShowCloseConfirmationDialog = true;
		}
		else
		{
			XLOG("Closing [%s]...", closeIter->filePath.filename().u8string().c_str());
			mScriptFiles.erase(closeIter);
		}
	}
}

void PixEditor::ShowCloseConfirmationDialog()
{
	ImGui::OpenPopup("Pix");

	if (ImGui::BeginPopupModal("Pix", &mShowCloseConfirmationDialog, ImGuiWindowFlags_AlwaysAutoResize))
	{
		ImGui::Text("Do you want to save changes to %s?", mLastFocusedScriptWindowId.c_str());
		ImGui::NewLine();
		ImGui::NewLine();
		ImGui::Separator();

		if (ImGui::Button("Save"))
		{
			if (Save())
			{
				CloseLastFocusedScriptWindow();
				mShowCloseConfirmationDialog = false;
			}
		}
		ImGui::SameLine();
		if (ImGui::Button("Don't Save"))
		{
			CloseLastFocusedScriptWindow();
			mShowCloseConfirmationDialog = false;
		}
		ImGui::SameLine();
		if (ImGui::Button("Cancel"))
		{
			mShowCloseConfirmationDialog = false;
		}
		ImGui::EndPopup();
	}
}

void PixEditor::ShowRenderView(float deltaTime)
{
	static float fps = 0.0f;
	static float frameCount = 0.0f;
	static float timeElapsed = 0.0f;

	// Track FPS
	frameCount += 1.0f;
	timeElapsed += deltaTime;
	if (timeElapsed > 1.0f)
	{
		fps = frameCount / timeElapsed;
		frameCount = 0.0f;
		timeElapsed = 0.0f;
	}

	char title[128];
	sprintf_s(title, "Render - fps: %.3f###Render", fps);
	ImGui::Begin(title, &mShowRenderView, ImGuiWindowFlags_AlwaysAutoResize);

	Graphics::NewFrame();
	mScriptParser.ExecuteScript();

	Viewport::Get()->DrawViewport();

	const float renderTextureWidth = static_cast<float>(X::GetRenderTextureWidth());
	const float renderTextureHeight = static_cast<float>(X::GetRenderTextureHeight());
	ImGui::Image(X::GetRenderTexture(), { renderTextureWidth, renderTextureHeight });

	mHasDockedWindow = ImGui::IsWindowDocked();
	
	if (ImGui::IsWindowFocused(ImGuiFocusedFlags_ChildWindows))
		mLastFocusedScriptWindowId.clear();

	ImGui::End();
}

void PixEditor::ShowAboutDialog()
{
	ImGui::OpenPopup("About Pix");

	if (ImGui::BeginPopupModal("About Pix", &mShowAboutDialog, ImGuiWindowFlags_AlwaysAutoResize))
	{
		const float imageWidth = (float)X::GetSpriteWidth(mLogoAbout);
		const float imageHeight = (float)X::GetSpriteHeight(mLogoAbout);
		const ImVec2 windowSize = ImGui::GetWindowSize();

		ImGui::SetCursorPosX((windowSize.x - imageWidth) * 0.5f);
		ImGui::Image(
			X::GetSprite(mLogoAbout),
			{ imageWidth, imageHeight },
			{ 0.0f, 0.0f },
			{ 1.0f, 1.0f },
			{ 1.0f, 1.0f, 1.0f, 0.1f });

		ImGui::Separator();
		ImGui::Text("Pix Editor\n\nCopyright (c) 2020 Peter Chan.\nAll rights reserved.");
		ImGui::EndPopup();
	}
}

void PixEditor::New()
{
	XLOG("New file...");

	// Create a new window
	mScriptFiles.push_back({});
	auto& textWindow = mScriptFiles.back();
	textWindow.filePath = "";
	textWindow.editor.SetLanguageDefinition(mLanguageDefinition);
	textWindow.editor.SetPalette(GetPixScriptPalette());
	textWindow.windowId = std::to_string(mNextWindowId++);

	SetNextWindowPosition();
}

void PixEditor::Open()
{
	XLOG("Open file...");

	char fileName[MAX_PATH] = {};
	if (!X::OpenFileDialog(fileName, "Open", sFileDialogFilters))
	{
		XLOG("Canceled.");
		return;
	}

	std::filesystem::path path = fileName;
	if (!path.has_filename())
	{
		XLOG("Invalid file name.");
		return;
	}

	auto iter = std::find_if(mScriptFiles.begin(), mScriptFiles.end(), [&path](auto& window) { return window.filePath == path; });
	if (iter != mScriptFiles.end())
	{
		XLOG("File already opened.");
		return;
	}

	XLOG("Opening [%s]...", path.u8string().c_str());

	std::ifstream file(path.u8string().c_str());
	if (!file.good())
	{
		XLOG("Failed to open file.");
		return;
	}

	// Create a new window
	mScriptFiles.push_back({});
	auto& textWindow = mScriptFiles.back();

	// Add file content
	std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
	textWindow.filePath = path;
	textWindow.editor.SetLanguageDefinition(mLanguageDefinition);
	textWindow.editor.SetPalette(GetPixScriptPalette());
	textWindow.windowId = path.filename().u8string();
	textWindow.editor.SetText(content);

	SetNextWindowPosition();
}

bool PixEditor::Save()
{
	XLOG("Save file...");

	auto iter = std::find_if(
		mScriptFiles.begin(),
		mScriptFiles.end(),
		[this](auto& script)
	{
		return mLastFocusedScriptWindowId == script.windowId && script.needSave;
	});
	if (iter == mScriptFiles.end())
	{
		XLOG("Nothing to save.");
		return true;
	}

	std::filesystem::path path;

	// Check if we have an existing file name
	auto& textWindow = *iter;
	if (textWindow.filePath.empty())
	{
		// Prompt for a new name
		char fileName[MAX_PATH] = {};
		if (!X::SaveFileDialog(fileName, "Save", sFileDialogFilters))
		{
			XLOG("Canceled.");
			return false;
		}

		path = fileName;
		if (!path.has_filename())
		{
			XLOG("Invalid file.");
			return false;
		}

		// Make sure we have a valid file extension
		if (!path.has_extension())
			path.replace_extension(sPixFileExtension);
	}
	else
	{
		// Save to existing file name
		path = textWindow.filePath;
	}

	XLOG("Saving [%s]...", path.u8string().c_str());

	std::ofstream file(path.u8string().c_str());
	if (file.good())
	{
		file << textWindow.editor.GetText();
		textWindow.filePath = path;
		textWindow.needSave = false;
	}

	return true;
}

bool PixEditor::SaveAs()
{
	// TODO: Implement this
	XLOG("Save As...");
	return false;
}

void PixEditor::Run(TextEditor* textEditor)
{
	XLOG("Run...");

	// If no editor is specified, find the currently focused editor
	if (textEditor == nullptr)
	{
		auto iter = std::find_if(
			mScriptFiles.begin(),
			mScriptFiles.end(),
			[this](auto& script)
		{
			return mLastFocusedScriptWindowId == script.windowId;
		});
		if (iter != mScriptFiles.end())
			textEditor = &iter->editor;
	}

	if (textEditor)
	{
		Save();
		VariableCache::Get()->Clear();
		mScriptParser.ParseScript(textEditor->GetText());
	}

	mShowRenderView = true;
}

void PixEditor::SetNextWindowPosition()
{
	if (mNextWindowPosX == 0.0f && mNextWindowPosY == 0.0f)
	{
		auto windowPos = ImGui::GetWindowPos();
		mNextWindowPosX = windowPos.x;
		mNextWindowPosY = windowPos.y;
	}

	mNextWindowPosX += 20.0f;
	mNextWindowPosY += 20.0f;
}

void PixEditor::CloseLastFocusedScriptWindow()
{
	auto iter = std::find_if(
		mScriptFiles.begin(),
		mScriptFiles.end(),
		[this](auto& script)
		{
			return mLastFocusedScriptWindowId == script.windowId;
		});
	if (iter != mScriptFiles.end())
	{
		XLOG("Closing [%s]...", iter->filePath.filename().u8string().c_str());
		mScriptFiles.erase(iter);
	}
}
