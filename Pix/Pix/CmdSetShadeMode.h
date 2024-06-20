#pragma once
#include "Command.h"

class CmdSetShadeMode : public Command
{
public:
	const char* GetName() override
	{
		return "SetShadeMode";
	}

	const char* GetDescription() override
	{
		return
			"SetShadeMode(<shadeMode>)\n"
			"\n"
			"-Sets the shade mode for the lighting (flat, gourand, phong).";
	}

	bool Execute(const std::vector<std::string>& params) override;
};
