#include "ModelManager.h"

ModelManager* ModelManager::Get()
{
	static ModelManager sInstance;
	return &sInstance;
}

void ModelManager::Clear()
{
	mModels.clear();
}

const Model* ModelManager::GetModel(const std::string& fileName)
{
	auto iter = std::find(mModels.begin(), mModels.end(), [fileName](auto& model)
		{
			return model->GetFileName() == fileName;

		});
	if (iter != mModels.end())
	{
		return iter->get();

	}
	auto& model = mModels.emplace_back(std::make_unique<Model>());
	model->Load(fileName);
	return model.get();
}
