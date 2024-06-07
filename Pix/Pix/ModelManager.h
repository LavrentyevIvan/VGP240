#pragma once

#include "Model.h"

class ModelManager
{
public:
	static ModelManager* Get();

	void Clear();
	const Model* GetModel(const std::string& fileName);

private:
	std::vector<std::unique_ptr<Model>> mModels;
};