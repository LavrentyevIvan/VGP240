#include "CmdPushRotationY.h"

#include "VariableCache.h"
#include "MatrixStack.h"

bool CmdPushRotationY::Execute(const std::vector<std::string>& params)
{
    // Need at least 2 params for x, y
    if (params.size() < 1)
        return false;

    auto vc = VariableCache::Get();
    float rad = vc->GetFloat(params[0]) * 3.1459 / 180.0f;
    MatrixStack::Get()->PushRotationY(rad);

    return true;
}