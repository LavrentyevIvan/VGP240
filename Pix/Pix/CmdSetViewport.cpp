#include "CmdSetViewport.h"
#include "Viewport.h"
#include "VariableCache.h"

bool CmdSetViewport::Execute(const std::vector<std::string>& params)
{
	if (params.size() < 4)
	{
		return false;
	}
	VariableCache* vc = VariableCache::Get();
	float x = vc->GetFloat(params[0]);
	float y = vc->GetFloat(params[1]);
	float width = vc->GetFloat(params[2]);
	float height = vc->GetFloat(params[3]);

	Viewport::Get()->SetViewport(x, y, width, height);

	return true;
}
