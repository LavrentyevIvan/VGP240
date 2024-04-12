#pragma once

#include <string>
#include <vector>

class ScriptParser
{
public:
	void ParseScript(const std::string& script);
	void ExecuteScript();

private:
	struct Statement
	{
		std::string command;
		std::vector<std::string> params;
	};

	std::vector<Statement> mStatements;
};
