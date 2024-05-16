#include "CmdSetCameraFar.h"
#include "VariableCache.h"
#include "Camera.h"

bool CmdSetCameraFar::Execute(const std::vector<std::string>& params)
{
	// Need at least 2 params for x, y
	if (params.size() < 1)
	{
		return false;
	}


	auto vc = VariableCache::Get();
	float Far = vc->GetFloat(params[0]);
	Camera::Get()->SetFarPlane({ Far });
	return true;
}