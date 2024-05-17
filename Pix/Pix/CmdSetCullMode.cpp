#include "CmdSetCullMode.h"
#include "PrimitiveManager.h"

bool CmdSetCullMode::Execute(const
	std::vector<std::string>& params)
{
	if (params.size() < 1)
	{
		return false;

	}

	CullMode cullMode = CullMode::None;
	if (params[0] == "none")
	{
		cullMode = CullMode::None;
	}
	else if (params[0] == "back")
	{
		cullMode = CullMode::Back;

	}
	else if (params[0] == "front")
	{
		cullMode = CullMode::Front;

	}
	else
	{
		return false;


	}
	PrimitivesManager::Get()->SetCullMode(cullMode);
	return true;
}
