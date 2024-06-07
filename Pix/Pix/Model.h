#pragma once
#include "Vertex.h"

class Model
{
public:
	void Load(const std::string& fileName);

	const std::string& GetFileName() const;
	const Vertex& GetVertex(uint32_t index) const;
	uint32_t GetVertexCount() const;
private:
	std::string mFileName;
	std::vector<Vertex> mVertices;
};