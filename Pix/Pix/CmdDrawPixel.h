#pragma once

#include "Command.h"

class CmdDrawPixel : public Command
{
public:
	const char* GetName() override
	{
		return "DrawPixel";
	}

	const char* GetDescription() override
	{
		return
			"DrawPixel(x, y)\n"
			"\n"
			"- Draws a single pixel at position (x, y).";
	}

	bool Execute(const std::vector<std::string>& params) override;
};
