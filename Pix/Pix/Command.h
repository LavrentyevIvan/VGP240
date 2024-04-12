#pragma once

#include <string>
#include <vector>

class Command
{
public:
	virtual ~Command() = default;

	virtual const char* GetName() = 0;
	virtual const char* GetDescription() = 0;

	virtual bool Execute(const std::vector<std::string>& params) = 0;
};
