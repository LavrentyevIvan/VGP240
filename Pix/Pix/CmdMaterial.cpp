#include "CmdMaterial.h"
#include "VariableCache.h"
#include "MaterialManager.h"

bool CmdSetMaterialAmbient::Execute(const std::vector<std::string>& params)
{
	if (params.size() < 3)
	{
		return false;
	}

	VariableCache* vc = VariableCache::Get();
	float r = vc->GetFloat(params[0]);
	float g = vc->GetFloat(params[1]);
	float b = vc->GetFloat(params[2]);

	MaterialManager::Get()->SetMaterialAmbient({ r,g,b,1.0f });
}

bool CmdSetMaterialDiffuse::Execute(const std::vector<std::string>& params)
{
	if (params.size() < 3)
	{
		return false;
	}

	VariableCache* vc = VariableCache::Get();
	float r = vc->GetFloat(params[0]);
	float g = vc->GetFloat(params[1]);
	float b = vc->GetFloat(params[2]);

	MaterialManager::Get()->SetMaterialDiffuse({ r,g,b,1.0f });
}

bool CmdSetMaterialSpecular::Execute(const std::vector<std::string>& params)
{
	if (params.size() < 3)
	{
		return false;
	}

	VariableCache* vc = VariableCache::Get();
	float r = vc->GetFloat(params[0]);
	float g = vc->GetFloat(params[1]);
	float b = vc->GetFloat(params[2]);

	MaterialManager::Get()->SetMaterialSpecular({ r,g,b,1.0f });
}
bool CmdSetMaterialEmissive::Execute(const std::vector<std::string>& params)
{
	if (params.size() < 3)
	{
		return false;
	}

	VariableCache* vc = VariableCache::Get();
	float r = vc->GetFloat(params[0]);
	float g = vc->GetFloat(params[1]);
	float b = vc->GetFloat(params[2]);

	MaterialManager::Get()->SetMaterialEmissive({ r,g,b, 1.0f});
}
bool CmdSetMaterialShininess::Execute(const std::vector<std::string>& params)
{
	if (params.size() < 1)
	{
		return false;
	}

	VariableCache* vc = VariableCache::Get();
	float shininess = vc->GetFloat(params[0]);
	

	MaterialManager::Get()->SetMaterialShininess({ shininess });
}
