#include"CmdAddVertex.h"
#include"PrimitiveManager.h"

bool CmdAddVertex::Execute(const std::vector<std::string>& params)
{
	float x, y, z = 0.0f;
	float r, g, b = 1.0f;
	if (params.size() == 2)
	{
		x = stof(params[0]);
		y = stof(params[1]);
	}
	else if (params.size() == 3)
	{
		x = stof(params[0]);
		y = stof(params[1]);
		z = stof(params[2]);
	}
	else if (params.size() == 5)
	{
		x = stof(params[0]);
		y = stof(params[1]);
		r = stof(params[2]);
		g = stof(params[3]);
		b = stof(params[4]);
	}
	else if (params.size() == 6)
	{
		x = stof(params[0]);
		y = stof(params[1]);
		z = stof(params[2]);
		r = stof(params[3]);
		g = stof(params[4]);
		b = stof(params[5]);
	}
	else
	{
		return false;

	}
	Vertex v;
	v.pos = { x,y,z };
	v.color = { r,g,b, 1.0f };
	PrimitivesManager::Get()->AddVertex(v);
	return true;

}
