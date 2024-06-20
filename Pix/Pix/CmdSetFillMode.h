#pragma once
#include "Command.h"

class CmdSetFillMode : public Command
{
public:
	const char* GetName() override
	{
		return "SetFillMode";
	}

	const char* GetDescription() override
	{
		return
			"SetFillMode(<fillmode>)\n"
			"\n"
			"-Sets the fillmode to read between vertices (wireframe and filled).";
	}

	bool Execute(const std::vector<std::string>& params) override;
}; 
