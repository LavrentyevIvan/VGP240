#include "CmdSetCameraFOV.h"
#include "VariableCache.h"
#include "Camera.h"

bool CmdSetCameraFOV::Execute(const std::vector<std::string>& params)
{
	// Need at least 2 params for x, y
	if (params.size() < 1)
	{
		return false;
	}


	auto vc = VariableCache::Get();
	float FOV = vc->GetFloat(params[0]) * 3.14159 / 180.0f;
	Camera::Get()->SetFOV({FOV});
	return true;
}