#pragma once
#include "Command.h"

class CmdEnableDepth : public Command
{
public:
	const char* GetName() override
	{
		return "EnableDepth";
	}

	const char* GetDescription() override
	{
		return
			"EnableDepth( <bool>)\n"
			"\n"
			"-Enable/Disable depth buffer. \n";
	}

	bool Execute(const std::vector<std::string>& params) override;
};