#pragma once
#include "Command.h"

class CmdSetCullMode : public Command
{
public:
	const char* GetName() override
	{
		return "SetCullMode";
	}

	const char* GetDescription() override
	{
		return
			"SetCullMOde(<cullmode>)\n"
			"\n"
			"Sets the triangle cull mode (none, back, front).";
	}

	bool Execute(const std::vector<std::string>& params) override;
};
