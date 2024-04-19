#include "Rasterizer.h"

Rasterizer* Rasterizer::Get()
{
	static Rasterizer sInstance;
	return &sInstance;
}

void Rasterizer::SetColor(X::Color color)
{
	mColor = color;
}

void Rasterizer::SetFillMode(FillMode fillmode)
{
	mFillMode = fillmode;
}

void Rasterizer::DrawPoint(int x, int y)
{
	X::DrawPixel(x, y, mColor);
}

void Rasterizer::DrawPoint(const Vertex& v)
{
	mColor = v.color;
	DrawPoint(static_cast<int>(v.pos.x+0.5f), static_cast<int>(v.pos.y+0.5f));
}

void Rasterizer::DrawLine(const Vertex& v0, const Vertex& v1)
{
	//we lerp from v0 to v1
	//draw point

	float dx = v1.pos.x - v0.pos.x;
	float dy = v1.pos.y - v0.pos.y;
	if (std::abs(dx) < 0.01f || std::abs(dx) <  std::abs(dy))
	{
		float startY, endY;
		X::Color startColor, endColor;
		if (v0.pos.y < v1.pos.y)
		{
			startY = v0.pos.y;
			endY = v1.pos.y;
		}
		else
		{
			startY = v1.pos.y;
			endY = v0.pos.y;
		}

		for (float y = startY; y <= endY;++y)
		{
			float t = (y - startY) / (endY - startY);
			Vertex v = LerpVertex(v0, v1, t);
			DrawPoint(v);

		}
	}
	else
	{
		float startX, endX;
		if (v0.pos.x < v1.pos.x)
		{
			startX = v0.pos.x;
			endX = v1.pos.x;
		}
		else 
		{
			startX = v1.pos.x;
			endX = v0.pos.x;
		}
		for (float x = startX; x <= endX; ++x)
		{
			float t = (x - startX) / (endX - startX);
			Vertex v = LerpVertex(v0, v1, t);
			DrawPoint(v);


		}
	}
}

void Rasterizer::DrawTriangle(const Vertex& v0, const Vertex& v1, const Vertex& v2)
{
	switch (mFillMode)
	{
	case FillMode::WireFrame:
		{
			DrawLine(v0,v1);
			DrawLine(v1,v2);
			DrawLine(v2,v0);
		}
		break;
	case FillMode::Solid:
	{
		DrawLine(v0, v1);
		DrawLine(v1, v2);
		DrawLine(v2, v0);
	}
	break;
	default:
		break;
}
