#include "CmdVarBool.h"

#include "VariableCache.h"

bool CmdVarBool::Execute(const std::vector<std::string>& params)
{
	// Need at leaset 3 params for name, =, value
	if (params.size() < 3)
		return false;

	auto vc = VariableCache::Get();
	if (!vc->IsVarName(params[0]) || params[1] != "=")
		return false;

	const float value = params[2] == "true";


	// Register variable
	vc->AddBool(params[0], value);
	return true;
}