#include "Model.h"

void Model::Load(const std::string& fileName)
{
	mFileName = fileName;

	std::vector<Vector3> positions;
	std::vector<Vector3> normals;
	std::vector<uint32_t> positionIndices;
	std::vector<uint32_t> normalsCount;

	FILE* file = nullptr;
	fopen_s(&file, fileName.c_str(), "r");
	if (file == nullptr)
	{
		char buffer[128];
		sprintf_s(buffer, "Cannot open model file %s", fileName.c_str());
		MessageBoxA(nullptr, buffer, "Model Error", MB_OK | MB_ICONEXCLAMATION);
		return;
	}

	while (true)
	{
		char buffer[128];
		int result = fscanf_s(file, "%s", buffer, (uint32_t)std::size(buffer));
		if (result == EOF)
		{
			break;
		}
		if (strcmp(buffer, "v") == 0)
		{
			float x, y, z = 0.0f;
			fscanf_s(file, "%f %f %f\n", &x, &y, &z);
			positions.push_back({ x, y, z });
		}
		else if (strcmp(buffer, "f") == 0)
		{
			uint32_t v[3];
			if (fscanf_s(file, "%d//%*d %d//%*d %d//%*d\n", &v[0], &v[1], &v[2]) != 3)
			{
				char error[128];
				sprintf_s(error, "Unexpected format for %s", fileName.c_str());
				MessageBoxA(nullptr, buffer, "Model Error", MB_OK | MB_ICONEXCLAMATION);
				return;
			}
			for (uint32_t i = 0; i < 3; i++)
			{
				positionIndices.push_back(v[i]);
			}

		}

	}
	fclose(file);

	mVertices.resize(positionIndices.size());
	normals.resize(positions.size());
	normalsCount.resize(positions.size());
	for (size_t i = 2; i < positionIndices.size(); i += 3)
	{
		uint32_t index0 = positionIndices[i - 2] - 1;
		uint32_t index1 = positionIndices[i - 1] - 1;
		uint32_t index2 = positionIndices[i] - 1;

		Vector3 pos0 = positions[index0];
		Vector3 pos1 = positions[index1];
		Vector3 pos2 = positions[index2];

		Vector3 faceNorm = MathHelper::Normalize(MathHelper::Cross((pos1 - pos0), (pos2 - pos0)));

		normals[index0] = normals[index0] + faceNorm;
		normals[index1] = normals[index1] + faceNorm;
		normals[index2] = normals[index2] + faceNorm;

		++normalsCount[index0];
		++normalsCount[index1];
		++normalsCount[index2];

	}

	for (size_t i = 0; i < normals.size(); i++)
	{
		if (normalsCount[i] > 0)
		{
			normals[i] = MathHelper::Normalize(normals[i] / static_cast<float>(normalsCount[i]));
		}
		else
		{
			normals[i] = { 0.0f, 1.0f, 0.0f };
		}
	}
	for (size_t i = 0; i < positionIndices.size(); i++)
	{
		mVertices[i].pos = positions[positionIndices[i] - 1];
		mVertices[i].norm = normals[positionIndices[i] - 1];
		mVertices[i].color = X::Colors::White;
	}

}

const std::string& Model::GetFileName() const
{
	return mFileName;
}

const Vertex& Model::GetVertex(uint32_t index) const
{
	return mVertices[index];
}

uint32_t Model::GetVertexCount() const
{
	return mVertices.size();
}