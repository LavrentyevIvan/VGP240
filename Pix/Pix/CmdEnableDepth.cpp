#include "CmdEnableDepth.h"
#include "DepthBuffer.h"
bool CmdEnableDepth::Execute(const std::vector<std::string>& params)
{
	if (params.size() < 1)
	{
		return false;
	}

	bool enable = params[0] == "true";
	DepthBuffer::Get()->SetEnabled(enable);
	return true;
}
