#pragma once

#include <memory>
#include <string>
#include <vector>

struct Variable;


class VariableCache
{
public:
	static VariableCache* Get();

public:
	void Clear();

	bool IsVarName(const std::string& name) const;

	void AddFloat(const std::string& name, float value, float speed = 0.01f, float min = -FLT_MIN, float max = FLT_MAX);
	float GetFloat(const std::string& param);

	void AddInt(const std::string& name, int value, int speed = 1, int min = -INT32_MIN, int max = INT32_MAX);
	float GetInt(const std::string& param);

	void AddBool(const std::string& name, bool value);
	bool GetBool(const std::string& param);


	void ShowEditor();

private:


	std::vector<std::unique_ptr<Variable>> mVariables;
};