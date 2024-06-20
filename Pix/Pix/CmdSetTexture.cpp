#include "CmdSetTexture.h"
#include "TextureManager.h"

bool CmdSetTexture::Execute(const std::vector<std::string>& params)
{
	if (params.size() < 1)
	{
		return false;
	}


	TextureManager::Get()->SetTexture(params[0]);
	return true;
}