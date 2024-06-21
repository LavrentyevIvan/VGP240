#pragma once
#include "MathHelper.h"
#include "XEngine.h"
struct Vertex
{
	Vector3 pos;
	Vector3 posWorld;
	Vector3 norm;
	X::Color color;
};

inline static Vector3 LerpPosition(const Vector3 a, const Vector3 b, float t, bool toPixel = true)
{
	Vector3 pos;
	
	pos.x = MathHelper::Lerp(a.x, b.x, t);
	pos.y = MathHelper::Lerp(a.y, b.y, t);
	pos.z = MathHelper::Lerp(a.z, b.z, t);

	if (toPixel)
	{
		pos.x = floorf(pos.x + 0.5f);
		pos.y = floorf(pos.y + 0.5f);
	}
	return pos;

}
inline static Vector3 LerpNormal(const Vector3 a, const Vector3 b, float t)
{
	Vector3 norm;
	X::Color color;
	norm = MathHelper::Lerp(a.x, b.x, t);
	norm = MathHelper::Lerp(a.y, b.y, t);
	norm = MathHelper::Lerp(a.z, b.z, t);
	return MathHelper::Normalize(norm);

}
inline static X::Color LerpColor(const X::Color a, const X::Color b, float t)
{
	X::Color color;
	color.r = MathHelper::Lerp(a.r, b.r, t);
	color.g = MathHelper::Lerp(a.g, b.g, t);
	color.b= MathHelper::Lerp(a.b, b.b, t);
	color.a= MathHelper::Lerp(a.a, b.a, t);
	return color;
}
inline static Vertex LerpVertex(const Vertex a, const Vertex b, float t, bool lerpNorm = false)
{
	Vertex vertex;
	vertex.pos = LerpPosition(a.pos, b.pos, t);
	vertex.color = LerpColor(a.color, b.color, t);
	if (lerpNorm)
	{
		vertex.posWorld = LerpPosition(a.posWorld, b.posWorld, t, false);
		vertex.norm = LerpNormal(a.norm, b.norm, t);
	}
	return vertex;
}