#include "CmdSetCameraDirection.h"
#include "VariableCache.h"
#include "Camera.h"

bool CmdSetCameraDirection::Execute(const std::vector<std::string>& params)
{
	// Need at least 2 params for x, y
	if (params.size() < 3)
	{
		return false;
	}


	auto vc = VariableCache::Get();
	float x = vc->GetFloat(params[0]);
	float y = vc->GetFloat(params[1]);
	float z = vc->GetFloat(params[2]);
	Camera::Get()->SetDirection({ x,y,z });
	return true;
}