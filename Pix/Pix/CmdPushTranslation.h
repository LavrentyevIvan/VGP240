#pragma once

#include "Command.h"

class CmdPushTranslation : public Command
{
public:
    const char* GetName() override
    {
        return "PushTranslation";
    }

    const char* GetDescription() override
    {
        return
            "PushTranslation(x,y,z)\n"
            "\n"
            "-translates triangle by (x, y, z).";
    }

    bool Execute(const std::vector<std::string>& params) override;
};
