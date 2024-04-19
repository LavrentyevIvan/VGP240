#pragma once
#include "Vertex.h"
enum class Topology
{
	Point,
	Line, 
	Triangle
};
class PrimitivesManager
{
public:
	static PrimitivesManager* Get();

	~PrimitivesManager();

	bool BeginDraw( Topology topology);
	void AddVertex( const Vertex& vertex);
	bool EndDraw();

private:
	PrimitivesManager();

	std::vector<Vertex> mVertexBuffer;
	Topology mTopology = Topology::Triangle;
	bool mDrawBegin = false;
};