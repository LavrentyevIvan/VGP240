//====================================================================================================
// Filename:	WinMain.h
// Created by:	Peter Chan
//====================================================================================================

#include "PixEditor.h"

int CALLBACK WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	PixEditor editor;

	X::Start("xconfig.json");
	editor.Initialize();

	X::Run([&](float deltaTime)
	{
		return editor.Run(deltaTime);
	});

	editor.Terminate();
	X::Stop();
	return 0;
}