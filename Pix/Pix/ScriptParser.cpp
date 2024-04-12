#include "ScriptParser.h"

#include "CommandDictionary.h"

#include <XEngine.h>
#include <sstream>

namespace
{
	auto TokenizeString(const std::string& inputString, const std::string& delimiters)
	{
		std::stringstream stringStream(inputString);
		std::string line;

		std::list<std::string> tokens;
		while (std::getline(stringStream, line))
		{
			std::size_t prev = 0;
			std::size_t pos = 0;

			while ((pos = line.find_first_of(delimiters.c_str(), prev)) != std::string::npos)
			{
				if (pos > prev)
					tokens.push_back(line.substr(prev, pos - prev));
				prev = pos + 1;
			}

			if (prev < line.length())
				tokens.push_back(line.substr(prev, std::string::npos));
		}

		return tokens;
	}
}

// Parse script into commands and parameters
void ScriptParser::ParseScript(const std::string& script)
{
	mStatements.clear();

	// Separate script into separate lines in a list
	auto scriptLines = TokenizeString(script, "\n");

	// For each command line, split out keyword and parameters
	for (auto& line : scriptLines)
	{
		// Ignore comments
		if (line.size() > 0 && line[0] == '/' && line[1] == '/')
			continue;

		auto tokens = TokenizeString(line, " ,()");
		if (tokens.empty())
			continue;

		auto it = tokens.begin();
		auto ie = tokens.end();

		Statement statement;
		statement.command = std::move(*it++);

		while (it != ie)
			statement.params.emplace_back(std::move(*it++));

		mStatements.emplace_back(std::move(statement));
	}
}

void ScriptParser::ExecuteScript()
{
	// Execute script commands
	for (auto& statement : mStatements)
	{
		Command* command = CommandDictionary::Get()->CommandLookup(statement.command);
		if (command == nullptr)
		{
			XLOG("Unknown command: %s", statement.command.c_str());
			continue;
		}
		if (!command->Execute(statement.params))
		{
			XLOG("Failed to run command: %s", statement.command.c_str());
		}
	}
}
