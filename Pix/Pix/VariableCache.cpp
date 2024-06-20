#include "VariableCache.h"

#include <ImGui/Inc/imgui.h>
#include <algorithm>

struct Variable
{
	virtual ~Variable() = default;
	virtual void ShowUI() = 0;

	std::string name;
};


struct FloatVar : public Variable
{
	void ShowUI() override
	{
		ImGui::DragFloat(name.c_str(), &value, speed, min, max);
	}

	float value = 0.0f;
	float speed = 1.0f;
	float min = -FLT_MIN;
	float max = -FLT_MAX;
};

struct IntVar : public Variable
{
	void ShowUI() override
	{
		ImGui::DragInt(name.c_str(), &value, speed, min, max);
	}

	int value = 0;
	int speed = 1;
	int min = -INT32_MIN;
	int max = -INT32_MAX;
};

struct BoolVar : public Variable
{
	void ShowUI() override
	{
		ImGui::Checkbox(name.c_str(), &value);
	}

	bool value = false;
};


VariableCache* VariableCache::Get()
{
	static VariableCache sInstance;
	return &sInstance;
}

void VariableCache::Clear()
{
	mVariables.clear();
}

bool VariableCache::IsVarName(const std::string& name) const
{
	return !name.empty() && name[0] == '$';
}

void VariableCache::AddFloat(const std::string& name, float value, float speed, float min, float max)
{
	// Add the variable if it does not already exist
	auto iter = std::find_if(mVariables.begin(), mVariables.end(), [name](auto& var)
		{
			return var->name == name;
		});
	if (iter == mVariables.end())
	{
		auto floatVar = std::make_unique<FloatVar>();
		floatVar->name = name;
		floatVar->value = value;
		floatVar->speed = speed;
		floatVar->max = max;
		floatVar->min = min;

		mVariables.emplace_back(std::move(floatVar));
	}
}

float VariableCache::GetFloat(const std::string& param)
{
	if (IsVarName(param))
	{
		auto iter = std::find_if(mVariables.begin(), mVariables.end(), [param](auto& var)
			{
				return var->name == param;
			});
		if (iter != mVariables.end())
		{
			return static_cast<FloatVar*>((*iter).get())->value;
		}
	}

	return stof(param);
}

void VariableCache::AddInt(const std::string& name, int value, int speed, int min, int max)
{
	// Add the variable if it does not already exist
	auto iter = std::find_if(mVariables.begin(), mVariables.end(), [name](auto& var)
		{
			return var->name == name;
		});
	if (iter == mVariables.end())
	{
		auto intVar = std::make_unique<IntVar>();
		intVar->name = name;
		intVar->value = value;
		intVar->speed = speed;
		intVar->max = max;
		intVar->min = min;

		mVariables.emplace_back(std::move(intVar));
	}
}

float VariableCache::GetInt(const std::string& param)
{
	if (IsVarName(param))
	{
		auto iter = std::find_if(mVariables.begin(), mVariables.end(), [param](auto& var)
			{
				return var->name == param;
			});
		if (iter != mVariables.end())
		{
			return static_cast<IntVar*>((*iter).get())->value;
		}
	}

	return stoi(param);
}

void VariableCache::AddBool(const std::string& name, bool value)
{
	// Add the variable if it does not already exist
	auto iter = std::find_if(mVariables.begin(), mVariables.end(), [name](auto& var)
		{
			return var->name == name;
		});
	if (iter == mVariables.end())
	{
		auto boolVar = std::make_unique<BoolVar>();
		boolVar->name = name;
		boolVar->value = value;

		mVariables.emplace_back(std::move(boolVar));
	}
}

bool VariableCache::GetBool(const std::string& param)
{
	if (IsVarName(param))
	{
		auto iter = std::find_if(mVariables.begin(), mVariables.end(), [param](auto& var)
			{
				return var->name == param;
			});
		if (iter != mVariables.end())
		{
			return static_cast<BoolVar*>((*iter).get())->value;
		}
	}

	return param == "true";
}

void VariableCache::ShowEditor()
{
	if (mVariables.empty())
		return;

	ImGui::Begin("Variables", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
	for (auto& var : mVariables)
		var->ShowUI();
	ImGui::End();
}