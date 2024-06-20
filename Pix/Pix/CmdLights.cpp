#include "CmdLights.h"
#include "VariableCache.h"
#include "LightManager.h"


bool CmdSetLightAmbient::Execute(const std::vector<std::string>& params)
{
	if (params.size() < 3)
	{
		return false;
	}

	VariableCache* vc = VariableCache::Get();
	float r = vc->GetFloat(params[0]);
	float g = vc->GetFloat(params[1]);
	float b = vc->GetFloat(params[2]);


	LightManager::Get()->SetLightingAmbient({ r, g, b, 1.0f });
	return true;
}

bool CmdSetLightDiffuse::Execute(const std::vector<std::string>& params)
{
	if (params.size() < 3)
	{
		return false;
	}

	VariableCache* vc = VariableCache::Get();
	float r = vc->GetFloat(params[0]);
	float g = vc->GetFloat(params[1]);
	float b = vc->GetFloat(params[2]);


	LightManager::Get()->SetLightingDiffuse({ r, g, b, 1.0f });
	return true;
}

bool CmdSetLightSpecular::Execute(const std::vector<std::string>& params)
{
	if (params.size() < 3)
	{
		return false;
	}

	VariableCache* vc = VariableCache::Get();
	float r = vc->GetFloat(params[0]);
	float g = vc->GetFloat(params[1]);
	float b = vc->GetFloat(params[2]);


	LightManager::Get()->SetLightingSpecular({ r, g, b, 1.0f });
	return true;
}


bool CmdAddDirectionalLight::Execute(const std::vector<std::string>& params)
{
	if (params.size() < 3)
	{
		return false;
	}

	VariableCache* vc = VariableCache::Get();
	float x = vc->GetFloat(params[0]);
	float y = vc->GetFloat(params[1]);
	float z = vc->GetFloat(params[2]);


	LightManager::Get()->AddDirectionalLight({ x, y, z });
	return true;
}


bool CmdAddPointLight::Execute(const std::vector<std::string>& params)
{
	if (params.size() < 3)
	{
		return false;
	}

	VariableCache* vc = VariableCache::Get();
	float x = vc->GetFloat(params[0]);
	float y = vc->GetFloat(params[1]);
	float z = vc->GetFloat(params[2]);

	float constant = 1.0f;
	float linear = 0.0f;
	float quadratic = 0.0f;

	if (params.size() > 3)
	{
		constant = vc->GetFloat(params[3]);
	}
	if (params.size() > 4)
	{
		linear = vc->GetFloat(params[4]);
	}
	if (params.size() > 5)
	{
		quadratic = vc->GetFloat(params[5]);
	}
	LightManager::Get()->AddPointLight({ x, y, z }, constant, linear, quadratic);
	return true;
}

bool CmdAddSpotLight::Execute(const std::vector<std::string>& params)
{
	if (params.size() < 6)
	{
		return false;
	}

	VariableCache* vc = VariableCache::Get();
	float posX = vc->GetFloat(params[0]);
	float posY = vc->GetFloat(params[1]);
	float posZ = vc->GetFloat(params[2]);


	float dirX = vc->GetFloat(params[3]);
	float dirY = vc->GetFloat(params[4]);
	float dirZ = vc->GetFloat(params[5]);

	float constant = 1.0f;
	float linear = 0.0f;
	float quadratic = 0.0f;
	float angle = 0.0f;
	float decay = 0.0f;

	if (params.size() > 6)
	{
		constant = vc->GetFloat(params[6]);
	}
	if (params.size() > 7)
	{
		linear = vc->GetFloat(params[7]);
	}
	if (params.size() > 8)
	{
		quadratic = vc->GetFloat(params[8]);
	}
	if (params.size() > 9)
	{
		angle = vc->GetFloat(params[9]) * X::Math::kDegToRad;
	}
	if (params.size() > 10)
	{
		decay = vc->GetFloat(params[10]);
	}
	LightManager::Get()->AddSpotLight({ posX, posY, posZ }, { dirX, dirY, dirZ }, constant, linear, quadratic, angle, decay);
	return true;
}