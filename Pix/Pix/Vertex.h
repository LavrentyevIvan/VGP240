#pragma once
#include "MathHelper.h"
#include "XEngine.h"
struct Vertex
{
	Vector3 pos;
	X::Color color;
};

inline static Vector3 LerpPosition(const Vector3 a, const Vector3 b, const float t)
{
	Vector3 pos;
	X::Color color;
	pos.x = floorf(MathHelper::Lerp(a.x, b.x, t) + 0.5);
	pos.y = floorf(MathHelper::Lerp(a.y, b.y, t) + 0.5);
	pos.z = floorf(MathHelper::Lerp(a.z, b.z, t) + 0.5);
	return pos;

}
inline static X::Color LerpColor(const X::Color a, const X::Color b, const float t)
{
	X::Color color;
	color.r = MathHelper::Lerp(a.r, b.r, t);
	color.g = MathHelper::Lerp(a.g, b.g, t);
	color.b= MathHelper::Lerp(a.b, b.b, t);
	color.a= MathHelper::Lerp(a.a, b.a, t);
	return color;
}
inline static Vertex LerpVertex(const Vertex a, const Vertex b, const float t)
{
	Vertex vertex;
	vertex.pos = LerpPosition(a.pos, b.pos, t);
	vertex.color = LerpColor(a.color, b.color, t);
	return vertex;
}