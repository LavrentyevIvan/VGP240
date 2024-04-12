#pragma once

#include "Command.h"
#include "TextEditor.h"

#include <list>
#include <map>

class CommandDictionary
{
public:
	static CommandDictionary* Get();

public:
	CommandDictionary();

	TextEditor::LanguageDefinition GenerateLanguageDefinition();

	Command* CommandLookup(const std::string& keyword);

private:
	template <class T>
	void RegisterCommand();

	std::map<std::string, std::unique_ptr<Command>> mCommandMap;
};
