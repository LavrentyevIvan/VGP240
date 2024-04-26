#include "Clipper.h"
#include "Viewport.h"

const short BIT_INSIDE	= 0;	//0000
const short BIT_LEFT	= 1 <<1;	//0001
const short BIT_RIGHT	= 1 <<2;	//0010
const short BIT_BOTTOM	= 1 <<3;	//0100
const short BIT_TOP		= 1 <<4;	//1000

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

	return true;
}
