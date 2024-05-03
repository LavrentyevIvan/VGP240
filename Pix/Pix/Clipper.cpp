#include "Clipper.h"
#include "Viewport.h"

const short BIT_INSIDE	= 0;	//0000
const short BIT_LEFT	= 1 <<1;	//0001
const short BIT_RIGHT	= 1 <<2;	//0010
const short BIT_BOTTOM	= 1 <<3;	//0100
const short BIT_TOP		= 1 <<4;	//1000

enum class ClipEdge : short

{
	Left,
	Top,
	Right,
	Bottom,
	Count
};
short GetOutputCode(float x, float y)
{
	Viewport* vp = Viewport::Get();

	short code = BIT_INSIDE;
	if (x < vp->GetMinX())
	{
		code |= BIT_LEFT; // 0001
	}
	else if (x > vp->GetMaxX())
	{
		code |= BIT_RIGHT; // 0010
	}
	if (y < vp->GetMinY())
	{
		code |= BIT_TOP; // 0001
	}
	else if (y > vp->GetMaxY())
	{
		code |= BIT_BOTTOM; // 0010
	}

	return code;
}

bool IsInFront(ClipEdge edge, const Vector3& pos)
{
	switch (edge)
	{
	case ClipEdge::Left: return pos.x > Viewport::Get()->GetMinX();
	case ClipEdge::Top: return pos.y > Viewport::Get()->GetMinY();
	case ClipEdge::Right: return pos.x < Viewport::Get()->GetMaxX();
	case ClipEdge::Bottom: return pos.y < Viewport::Get()->GetMaxY();
	default:
		break;
	}
}

Vertex ComputeIntersection(ClipEdge edge, const Vertex& v, const Vertex& vp1)
{
	float t = 0.0f;

	switch (edge)
	{
	case ClipEdge::Left:
	{
		t = (Viewport::Get()->GetMinX() - v.pos.x) / (vp1.pos.x - v.pos.x);
	}
	break;
	case ClipEdge::Top:
	{
		t = (Viewport::Get()->GetMinY() - v.pos.y) / (vp1.pos.y - v.pos.y);

	}
	break;
	case ClipEdge::Right:
	{
		t = (Viewport::Get()->GetMaxX() - v.pos.x) / (vp1.pos.x - v.pos.x);

	}
	break;
	case ClipEdge::Bottom:
	{
		t = (Viewport::Get()->GetMaxY() - v.pos.y) / (vp1.pos.y - v.pos.y);

	}
	break;
	default:
		break;
	}
	return LerpVertex(v, vp1, t);

}

Clipper* Clipper::Get()
{
	static Clipper sInstance;
	return &sInstance;
}
Clipper::Clipper()
{

}

void Clipper::OnNewFrame()
{
	mClipping = false;
}

bool Clipper::ClipPoint(const Vertex& v)
{
	if (!mClipping)
	{
		return false;
	}

	Viewport* vp = Viewport::Get();
	float maxX = vp->GetMaxX();
	float minX = vp->GetMinX();
	float maxY = vp->GetMaxX();
	float minY = vp->GetMinY();

	

	return v.pos.x < minX || v.pos.x > maxX || v.pos.y < minY || v.pos.y > maxY;

}

bool Clipper::ClipLine(Vertex& v0, Vertex& v1)
{
	if (!mClipping)
	{
		return false;
	}

	Viewport* vp = Viewport::Get();
	float maxX = vp->GetMaxX();
	float minX = vp->GetMinX();
	float maxY = vp->GetMaxX();
	float minY = vp->GetMinY();
	short codeV0 = GetOutputCode(v0.pos.x, v0.pos.y);
	short codeV1 = GetOutputCode(v1.pos.x, v1.pos.y);

	bool cullLine = true;
	while (true)
	{
		if (!(codeV0 | codeV1))
		{
			//if both are 0000 BIT_INSIDE then valid
			cullLine = false;
			break;
		}
		else if (codeV0 & codeV1) //1000 & 1010
		{
			//both vertices are in the same line, so cull it
			cullLine = true;
			break;
		}

		float t = 0.0f;
		short outcodeOut = codeV1 > codeV0 ? codeV1 : codeV0;

		if (outcodeOut & BIT_TOP)
		{
			t = (minY - v0.pos.y) / (v1.pos.y - v0.pos.y);

		}
		else if (outcodeOut & BIT_BOTTOM)
		{
			t = (maxY - v0.pos.y) / (v1.pos.y - v0.pos.y);

		}else if (outcodeOut & BIT_LEFT)
		{
			t = (minX - v0.pos.y) / (v1.pos.y - v0.pos.y);

		}else if (outcodeOut & BIT_RIGHT)
		{
			t = (maxX - v0.pos.y) / (v1.pos.y - v0.pos.y);

		}
		
		if (outcodeOut == codeV0)
		{
			v0 = LerpVertex(v0, v1, t);
			codeV0 = GetOutputCode(v0.pos.x, v0.pos.y);
		}
		else
		{
			v1 = LerpVertex(v0, v1, t);
			codeV1 = GetOutputCode(v1.pos.x, v1.pos.y);
		}
	}
	return cullLine;
}

bool Clipper::ClipTriangle(std::vector<Vertex>& vertices)
{
	if (!mClipping)
	{
		return false;
	}
	std::vector<Vertex> newVertices;
	for (int i = 0; i < (int)ClipEdge::Count; ++i)
	{
		newVertices.clear();
		ClipEdge edge = (ClipEdge)i;
		for (size_t v = 0; v < vertices.size(); ++v)
		{
			//
			size_t vp1 = (v + 1) % vertices.size();
			const Vertex& vertex = vertices[v];
			const Vertex& vertexP1 = vertices[vp1];
			
			const bool vIsInFront = IsInFront(edge, vertex.pos);
			const bool vp1IsInFront = IsInFront(edge, vertexP1.pos);
			//CASE1: both are in front
			if (vIsInFront && vp1IsInFront)
			{
				newVertices.push_back(vertexP1);
			}
			//CASE2: both are behind
			else if (!vIsInFront && !vp1IsInFront)
			{
				//dont save anything
			}
			//CASE3: v is in front and vp1 is behind
			else if (vIsInFront && !vp1IsInFront)
			{
				newVertices.push_back(ComputeIntersection(edge, vertex, vertexP1));
			}
			
			//CASE4: v is behind and vp1 is in front
			else if (!vIsInFront && vp1IsInFront)
			{
				newVertices.push_back(ComputeIntersection(edge, vertex, vertexP1));
				newVertices.push_back(vertexP1);
			}
		
		}
		vertices = newVertices;
	}

	return newVertices.empty();
}
