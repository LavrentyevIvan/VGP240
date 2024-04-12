#pragma once

#include "Command.h"

class CmdSetResolution : public Command
{
public:
	const char* GetName() override
	{
		return "SetResolution";
	}

	const char* GetDescription() override
	{
		return
			"SetResolution(width, height, <pixelSize>, <showGrid>)\n"
			"\n"
			"- Sets the render view resolution.\n"
			"- Optional: Set pixel size, default = 1.\n"
			"- Optional: Show grid (true or false) if pixel size is > 1.\n";
	}

	bool Execute(const std::vector<std::string>& params) override;
};
