#pragma once

#pragma once
#include "Command.h"
class CmdSetLightAmbient : public Command
{
public:
	const char* GetName() override
	{
		return "SetLightAmbient";
	}

	const char* GetDescription() override
	{
		return
			"SetLightAmbient( r, g, b)\n"
			"\n"
			"- sets ambient color for light";

	}

	bool Execute(const std::vector<std::string>& params) override;
};

class CmdSetLightDiffuse : public Command
{
public:
	const char* GetName() override
	{
		return "SetLightDiffuse";
	}

	const char* GetDescription() override
	{
		return
			"SetLightDiffuse( r, g, b)\n"
			"\n"
			"- sets diffuse color for light";

	}

	bool Execute(const std::vector<std::string>& params) override;
};

class CmdSetLightSpecular: public Command
{
public:
	const char* GetName() override
	{
		return "SetLightSpecular";
	}

	const char* GetDescription() override
	{
		return
			"SetLightSpecular( r, g, b)\n"
			"\n"
			"- sets specular color for light";

	}

	bool Execute(const std::vector<std::string>& params) override;
};

class CmdAddDirectionalLight: public Command
{
public:
	const char* GetName() override
	{
		return "AddDirectionalLight";
	}

	const char* GetDescription() override
	{
		return
			"AddDirectionalLight(x,y,z)\n"
			"\n"
			"- adds directional light to manager";

	}

	bool Execute(const std::vector<std::string>& params) override;
};