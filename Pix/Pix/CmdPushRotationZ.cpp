#include "CmdPushRotationZ.h"

#include "VariableCache.h"
#include "MatrixStack.h"

bool CmdPushRotationZ::Execute(const std::vector<std::string>& params)
{
    // Need at least 2 params for x, y
    if (params.size() < 1)
        return false;

    auto vc = VariableCache::Get();
    float rad = vc->GetFloat(params[0]) * 3.1459 / 180.0f;
    MatrixStack::Get()->PushRotationZ(rad);

    return true;
}