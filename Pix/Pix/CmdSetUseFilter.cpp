#include "CmdSetUseFilter.h"
#include "TextureManager.h"


bool CmdSetUseFilter::Execute(const std::vector<std::string>& params)
{
	if (params.size() < 1)
		return false;

	bool useFilter = params[0] == "true";

	TextureManager::Get()->SetUseFilter(useFilter);
	return true;
}