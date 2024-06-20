#pragma once

#include "Command.h"

class CmdSetUseFilter : public Command
{
public:
	const char* GetName() override
	{
		return "SetUseFilter";
	}

	const char* GetDescription() override
	{
		return
			"SetUseFilter(x, y)\n"
			"\n"
			"- Draws a single pixel at position (x, y).";
	}

	bool Execute(const std::vector<std::string>& params) override;
};