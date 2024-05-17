#pragma once

#include "Command.h"

class CmdPushRotationZ : public Command
{
public:
    const char* GetName() override
    {
        return "PushRotationZ";
    }

    const char* GetDescription() override
    {
        return
            "CmdPushRotationZ(deg)\n"
            "\n"
            "- push rotation into matrix stack (x, y).";
    }

    bool Execute(const std::vector<std::string>& params) override;
};
