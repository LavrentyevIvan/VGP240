#pragma once
#include "Command.h"

class CmdSetCameraDirection : public Command
{
public:
	const char* GetName() override
	{
		return "SetCameraDirection";
	}

	const char* GetDescription() override
	{
		return
			"SetCameraDirection(x, y,z)\n"
			"\n"
			"- Sets camera direction to (x, y, z).";
	}

	bool Execute(const std::vector<std::string>& params) override;
};