#pragma once

#include "Command.h"

class CmdModel : public Command
{
public:
	const char* GetName() override
	{
		return "Model";
	}

	const char* GetDescription() override
	{
		return
			"BeginDraw(topology)\n"
			"\n"
			"- begins draw\n- Stores topologies";
	}

	bool Execute(const std::vector<std::string>& params) override;
};