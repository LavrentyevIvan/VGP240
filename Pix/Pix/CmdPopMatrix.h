#pragma once
#include "Command.h"

class CmdPopMatrix : public Command
{
public:
	const char* GetName() override
	{
		return "PopMatrix";
	}

	const char* GetDescription() override
	{
		return
			"PopMatrix(x, y)\n"
			"\n"
			"- Push Rotation into matrix stack (x, y).";
	}

	bool Execute(const std::vector<std::string>& params) override;
};

