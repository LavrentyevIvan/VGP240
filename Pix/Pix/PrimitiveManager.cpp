#include "PrimitiveManager.h"
#include "Rasterizer.h"
#include "Clipper.h"
#include "Camera.h"
#include "MatrixStack.h"
#include "LightManager.h"
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

	bool CullTriangle(CullMode mode, const std::vector<Vertex>& triangleInNDC)
	{
		if (mode == CullMode::None)
		{
			return false;
		}
		Vector3 abDir = triangleInNDC[1].pos - triangleInNDC[0].pos;
		Vector3 acDir = triangleInNDC[2].pos - triangleInNDC[0].pos;
		Vector3 faceNorm = MathHelper::Normalize(MathHelper::Cross(abDir, acDir));
		if (mode == CullMode::Back)
		{
			return faceNorm.z > 0.0f;
		}
		if (mode == CullMode::Front)
		{
			return faceNorm.z < 0.0f;
		}
		return false;
		
	}
}

PrimitivesManager::PrimitivesManager()
{
}
PrimitivesManager::~PrimitivesManager()
{
}
void PrimitivesManager::OnNewFrame()
{
	mCullMode = CullMode::None;
	mCorrectUV = false;
}

void PrimitivesManager::SetCullMode(CullMode mode)
{
	mCullMode = mode;
}


PrimitivesManager* PrimitivesManager::Get()
{
	static PrimitivesManager sInstance;
	return &sInstance;
}

bool PrimitivesManager::BeginDraw(Topology topology, bool applyTransform)
{
	mTopology = topology;
	mApplyTransform = applyTransform;
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


	switch (mTopology)
	{
	case Topology::Point:
	{
		for (size_t i = 0; i < mVertexBuffer.size(); i++)
		{
			if (!Clipper::Get()->ClipPoint(mVertexBuffer[i]))
			{
				Rasterizer::Get()->DrawPoint(mVertexBuffer[i]);
			}
		}
	}
	break;
	case Topology::Line: {
		for (size_t i = 1; i < mVertexBuffer.size(); i += 2)
		{
			if (!Clipper::Get()->ClipLine(mVertexBuffer[i - 1], mVertexBuffer[i]))
			{
				Rasterizer::Get()->DrawLine(mVertexBuffer[i - 1], mVertexBuffer[i]);
			}
		}
	}
	 break;
	case Topology::Triangle: {

		Matrix4 matWorld = MatrixStack::Get()->GetTransform();
		Matrix4 matView = Camera::Get()->GetViewMatrix();
		Matrix4 matProj = Camera::Get()->GetProjectionMatrix();
		Matrix4 matScreen = GetScreenMatrix();
		Matrix4 MatNDC = matView * matProj;
		LightManager* lm = LightManager::Get();

		for (size_t i = 2; i < mVertexBuffer.size(); i += 3)
		{
			std::vector<Vertex> triangle = { mVertexBuffer[i - 2], mVertexBuffer[i - 1], mVertexBuffer[i] };

			if (mApplyTransform)
			{
				//move the position into world space
				for (size_t t = 0; t < triangle.size(); t++)
				{
					Vector3 worldPos = MathHelper::TransformCoord(triangle[t].pos, matWorld);
					triangle[t].pos = worldPos;
					triangle[t].posWorld = worldPos;
				}
				if (MathHelper::CheckEqual(MathHelper::MagnitudeSquared(triangle[0].norm), 0.0f))
				{
					//apply world spacew lights to verts
					Vector3 dirAB = triangle[1].pos - triangle[0].pos;
					Vector3 dirAC = triangle[2].pos - triangle[0].pos;
					Vector3 faceNormal = MathHelper::Normalize(MathHelper::Cross(dirAB, dirAC));
					for (size_t t = 0; t < triangle.size(); t++)
					{
						triangle[t].norm = faceNormal;
					}

				}
				if (triangle[0].color.z >= 0.0f)
				{
					if (Rasterizer::Get()->GetShadeMode() == ShadeMode::Flat || Rasterizer::Get()->GetShadeMode() == ShadeMode::Gouraud)
					{
						for (size_t t = 0; t < triangle.size(); t++)
						{
							triangle[t].color *= LightManager::Get()->ComputeLightColor(triangle[t].pos, triangle[t].norm);
						}
					}
				}
				else if (mCorrectUV)
				{
					for (size_t t = 0; t < triangle.size(); t++)
					{
						Vector3 viewPos = MathHelper::TransformCoord(triangle[t].pos, matView);
						triangle[t].color.x /= viewPos.z;
						triangle[t].color.y /= viewPos.z;
						triangle[t].color.w = 1.0f / viewPos.z;
					}
				}

				

				//move the positions to ndc space
				for (size_t t = 0; t < triangle.size(); t++)
				{
					Vector3 ndcPos = MathHelper::TransformCoord(triangle[t].pos, MatNDC);
					triangle[t].pos = ndcPos;
				}
				//do culling test
				if (CullTriangle(mCullMode, triangle))
				{
					continue;
				}
				//move pos to screen space
				for (size_t t = 0; t < triangle.size(); t++)
				{
					Vector3 screenPos = MathHelper::TransformCoord(triangle[t].pos, matScreen);
					screenPos.x = floor(screenPos.x + 0.5f);
					screenPos.y = floor(screenPos.y + 0.5f);

					triangle[t].pos = screenPos;
				}

			}
			if (!Clipper::Get()->ClipTriangle(triangle))
			{
				for (size_t t = 2; t < triangle.size(); t++)
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

	return true;

}

void PrimitivesManager::SetCorrectUV(bool correctUV)
{
	mCorrectUV = correctUV;
}