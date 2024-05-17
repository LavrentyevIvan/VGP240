#pragma once

#include "Command.h"

class CmdPushRotationY : public Command
{
public:
    const char* GetName() override
    {
        return "PushRotationY";
    }

    const char* GetDescription() override
    {
        return
            "CmdPushRotationY(deg)\n"
            "\n"
            "- push rotation into matrix stack (x, y).";
    }

    bool Execute(const std::vector<std::string>& params) override;
}; 
