#include "PrimitiveManager.h"
#include "Rasterizer.h"
#include "Clipper.h"
#include "Camera.h"
extern float gResolutionX;
extern float gResolutionY;

namespace
{
	Matrix4 GetScreenMatrix()
	{
		float hw = gResolutionX * 0.5f;
		float hh = gResolutionY * 0.5f;
		return Matrix4(
			hw, 0.0f, 0.0f, 0.0f,
			0.0f, -hh, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			hw, hh, 0.0f, 1.0f
		);


	}
}

PrimitivesManager::PrimitivesManager()
{
}
PrimitivesManager::~PrimitivesManager()
{
}
PrimitivesManager* PrimitivesManager::Get()
{
	static PrimitivesManager sInstance;
	return &sInstance;
}

bool PrimitivesManager::BeginDraw(Topology topology, bool applyTransform){
	mTopology = topology;
	mDrawBegin = true;
	mVertexBuffer.clear();
	return true;
}

void PrimitivesManager::AddVertex(const Vertex& vertex)
{
	if (mDrawBegin)
	{
		mVertexBuffer.push_back(vertex);
	}
}

bool PrimitivesManager::EndDraw()
{
	if (!mDrawBegin)
	{
		return false;
	}
	if (mApplyTransform)
	{
		Matrix4 matWorld = Matrix4::Identity();
		Matrix4 matView = Camera::Get()->GetViewMatrix();
		Matrix4 matProj = Camera::Get()->GetProjectionMatrix();
		Matrix4 matScreen = GetScreenMatrix();
		Matrix4 matNDC = matWorld * matView * matProj;
		Matrix4 matFinal = matNDC * matScreen;
		for (size_t i = 0; i < mVertexBuffer.size(); ++i)
		{
			Vector3 finalPos = MathHelper::TransformCoord(mVertexBuffer[i].pos, matFinal);
			finalPos.x = floor(finalPos.x + 0.5f);
			finalPos.y = floor(finalPos.y + 0.5f);
			finalPos.z = floor(finalPos.z + 0.5f);
			mVertexBuffer[i].pos = finalPos;
		}

	}
	switch (mTopology)
	{
	case Topology::Point:
	{
		for (size_t i = 0; i < mVertexBuffer.size(); ++i)
		{
			if (!Clipper::Get()->ClipPoint(mVertexBuffer[i-1]))
			{
				Rasterizer::Get()->DrawPoint(mVertexBuffer[i]);
			}
		}
	}
	break;
	case Topology::Line:
	{
		for (size_t i = 1; i < mVertexBuffer.size(); i+=2)
		{
			if (!Clipper::Get()->ClipLine(mVertexBuffer[i - 1], mVertexBuffer[i]))
			{
				Rasterizer::Get()->DrawLine(mVertexBuffer[i - 1], mVertexBuffer[i]);
			}
		}
	}
	break;
	case Topology::Triangle:
	{
		for (size_t i = 2; i < mVertexBuffer.size(); i+=3)
		{
			std::vector<Vertex> triangle = { mVertexBuffer[i - 2],mVertexBuffer[i - 1],mVertexBuffer[i] };
			if (!Clipper::Get()->ClipTriangle(triangle))
			{
				for (size_t t = 2; t < triangle.size(); ++t)
				{
					Rasterizer::Get()->DrawTriangle(triangle[0], triangle[t - 1], triangle[t]);
				}
			}
		}
	}
	break;
	default:
		break;
	}
}