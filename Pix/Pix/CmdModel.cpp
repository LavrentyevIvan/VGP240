#include "CmdModel.h"
#include "ModelManager.h"
#include "PrimitiveManager.h"

bool CmdModel::Execute(const std::vector<std::string>& params)
{
	if (params.size() < 1)
	{
		return false;
	}


	const Model* model = ModelManager::Get()->GetModel(params[0]);
	PrimitivesManager* pm = PrimitivesManager::Get();
	for (uint32_t i = 0; i < model->GetVertexCount(); i++)
	{
		pm->AddVertex(model->GetVertex(i));
	}
	return true;
}