#pragma once

#include "Command.h"

class CmdPushRotationX : public Command
{
public:
    const char* GetName() override
    {
        return "PushRotationX";
    }

    const char* GetDescription() override
    {
        return
            "CmdPushRotationX(deg)\n"
            "\n"
            "- push rotation into matrix stack (x, y).";
    }

    bool Execute(const std::vector<std::string>& params) override;
};