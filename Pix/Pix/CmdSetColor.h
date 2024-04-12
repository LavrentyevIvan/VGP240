#pragma once

#include "Command.h"

class CmdSetColor : public Command
{
public:
	const char* GetName() override
	{
		return "SetColor";
	}

	const char* GetDescription() override
	{
		return
			"SetColor(r, g, b)\n"
			"\n"
			"- Sets the color using red, green, and blue. Values are from 0.0 to 1.0.";
	}

	bool Execute(const std::vector<std::string>& params) override;
};
