#pragma once

#include "Command.h"

class CmdSetCorrectUV : public Command
{
public:
	const char* GetName() override
	{
		return "SetCorrectUV";
	}

	const char* GetDescription() override
	{
		return
			"CorrectUV\n"
			"\n"
			"- Draws a single pixel at position (none back front).";
	}

	bool Execute(const std::vector<std::string>& params) override;
};