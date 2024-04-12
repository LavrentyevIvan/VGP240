//====================================================================================================
// Filename:	PixEditor.h
// Created by:	Peter Chan
//====================================================================================================

#pragma once

#include "ScriptParser.h"
#include "TextEditor.h"
#include <XEngine.h>

class PixEditor
{
public:
	void Initialize();
	void Terminate();

	bool Run(float deltaTime);

private:
	void ShowMenuBar();
	void ShowFileMenu();
	void ShowEditMenu();
	void ShowViewMenu();
	void ShowHelpMenu();

	void ShowMainWindowWithDockSpace();
	void ShowLogo();
	void ShowScriptFileWindows();
	void ShowCloseConfirmationDialog();
	void ShowRenderView(float deltaTime);
	void ShowAboutDialog();

	void New();
	void Open();
	bool Save();
	bool SaveAs();

	void Run(TextEditor* textEditor = nullptr);

	void SetNextWindowPosition();
	void CloseLastFocusedScriptWindow();

private:
	struct ScriptFile
	{
		std::filesystem::path filePath;
		TextEditor editor;
		std::string windowId;
		bool needSave = false;
	};

	TextEditor::LanguageDefinition mLanguageDefinition;

	X::TextureId mLogo;
	X::TextureId mLogoAbout;
	std::list<ScriptFile> mScriptFiles;
	std::string mLastFocusedScriptWindowId;
	int mNextWindowId = 0;
	float mNextWindowPosX = 0.0f;
	float mNextWindowPosY = 0.0f;
	bool mShowRenderView = false;
	bool mShowCloseConfirmationDialog = false;
	bool mShowAboutDialog = false;
	bool mHasDockedWindow = false;
	bool mRequestQuit = false;

	ScriptParser mScriptParser;
};