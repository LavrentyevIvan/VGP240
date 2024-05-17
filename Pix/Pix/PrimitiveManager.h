#pragma once
#include "Vertex.h"
enum class Topology
{
	Point,
	Line, 
	Triangle
};
enum class CullMode
{
	None, //dont cull nothin
	Back, //cull back facing
	Front //cull front facing
};
class PrimitivesManager
{
public:
	static PrimitivesManager* Get();

	~PrimitivesManager();

	void OnNewFrame();
	void SetCullMode(CullMode mode);

	bool BeginDraw(Topology topology, bool applyTransform = false);
	void AddVertex( const Vertex& vertex);
	bool EndDraw();

private:
	PrimitivesManager();

	std::vector<Vertex> mVertexBuffer;
	Topology mTopology = Topology::Triangle;
	CullMode mCullMode = CullMode::None;
	bool mDrawBegin = false;
	bool mApplyTransform = false;
};