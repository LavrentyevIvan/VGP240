#pragma once

#include "Command.h"

class CmdSetAddressMode : public Command
{
public:
	const char* GetName() override
	{
		return "SetAddressMode";
	}

	const char* GetDescription() override
	{
		return
			"AddressMode(address mode)\n"
			"\n"
			"- Draws a single pixel at position (none back front).";
	}

	bool Execute(const std::vector<std::string>& params) override;
};