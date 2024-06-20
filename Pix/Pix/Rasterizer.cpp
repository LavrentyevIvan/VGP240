#include "Rasterizer.h"
#include "DepthBuffer.h"
#include "LightManager.h"
#include "TextureManager.h"

Rasterizer* Rasterizer::Get()
{
	static Rasterizer sInstance;
	return &sInstance;
}

void Rasterizer::SetColor(X::Color color)
{
	mColor = color;
}

void Rasterizer::SetFillMode(FillMode fillMode)
{
	mFillMode = fillMode;
}

void Rasterizer::SetShadeMode(ShadeMode shadeMode)
{
	mShadeMode = shadeMode;
}

ShadeMode Rasterizer::GetShadeMode()
{
	return mShadeMode;
}

void Rasterizer::DrawPoint(int x, int y)
{
	X::DrawPixel(x, y, mColor);
}

void Rasterizer::DrawPoint(const Vertex& v)
{
	if (DepthBuffer::Get()->CheckDepthBuffer(v.pos.x, v.pos.y, v.pos.z))
	{
		mColor = TextureManager::Get()->SampleColor(v.color);
		if (mShadeMode == ShadeMode::Phong)
		{
			mColor *= LightManager::Get()->ComputeLightColor(v.posWorld, v.norm);
		}
		DrawPoint(static_cast<int>(v.pos.x), static_cast<int>(v.pos.y));
	}
}

void Rasterizer::DrawLine(const Vertex& v0, const Vertex& v1)
{

	float dx = v1.pos.x - v0.pos.x;
	float dy = v1.pos.y - v0.pos.y;
	if (std::abs(dx) < 0.01f || std::abs(dx) < std::abs(dy))
	{
		//slope is stright up
		int startY, endY;
		X::Color startColor, endColor;
		if (v0.pos.y < v1.pos.y)
		{
			startY = static_cast<int>(v0.pos.y);
			endY = static_cast<int>(v1.pos.y);
		}
		else
		{
			startY = static_cast<int>(v1.pos.y);
			endY = static_cast<int>(v0.pos.y);
		}

		for (float y = startY; y <= endY; y++)
		{
			float t = static_cast<float>(y - startY) / static_cast<float>(endY - startY);
			Vertex v = LerpVertex(v0, v1, t, mShadeMode == ShadeMode::Phong);
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

		for (float x = startX; x <= endX; x++)
		{
			float t = static_cast<float>(x - startX) / static_cast<float>(endX - startX);
			Vertex v = LerpVertex(v0, v1, t, mShadeMode == ShadeMode::Phong);
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
		DrawLine(v0, v1);
		DrawLine(v1, v2);
		DrawLine(v2, v0);
	}
	break;
	case FillMode::Solid:
	{
		std::vector<Vertex> sortedVertices = { v0, v1, v2 };
		std::sort(sortedVertices.begin(), sortedVertices.end(), [](const Vertex& lhs, const Vertex& rhs)
			{
				return lhs.pos.y < rhs.pos.y;
			});
		if (mShadeMode == ShadeMode::Flat)
		{
			sortedVertices[1].color = sortedVertices[0].color;
			sortedVertices[2].color = sortedVertices[0].color;
		}
		DrawFilledTriangle(sortedVertices[0], sortedVertices[1], sortedVertices[2]);

	}
	break;
	default:
		break;
	}

}
void Rasterizer::DrawFilledTriangle(const Vertex& v0, const Vertex& v1, const Vertex& v2)
{

	float dy = v2.pos.y - v0.pos.y;
	int startY = static_cast<int>(v0.pos.y);
	int endY = static_cast<int>(v2.pos.y);

	if (MathHelper::CheckEqual(dy, 0.0f))
	{
		DrawLine(v0, v2);
	}
	else if (MathHelper::CheckEqual(v0.pos.y, v1.pos.y))
	{
		for (int y = startY; y <= endY; ++y)
		{
			float t = static_cast<float>(y - startY) / dy;
			Vertex a = LerpVertex(v0, v2, t, mShadeMode == ShadeMode::Phong);
			Vertex b = LerpVertex(v1, v2, t, mShadeMode == ShadeMode::Phong);
			DrawLine(a, b);
		}
	}
	else if (MathHelper::CheckEqual(v1.pos.y, v2.pos.y))
	{
		for (int y = startY; y <= endY; ++y)
		{
			float t = static_cast<float>(y - startY) / dy;
			Vertex a = LerpVertex(v0, v2, t, mShadeMode == ShadeMode::Phong);
			Vertex b = LerpVertex(v0, v1, t, mShadeMode == ShadeMode::Phong);
			DrawLine(a, b);
		}
	}
	else
	{
		float t = (v1.pos.y - v0.pos.y) / dy;
		Vertex splitVertex = LerpVertex(v0, v2, t, mShadeMode == ShadeMode::Phong);

		//Top fill
		DrawFilledTriangle(v0, v1, splitVertex);
		//botom fill
		DrawFilledTriangle(v1, splitVertex, v2);
	}


}