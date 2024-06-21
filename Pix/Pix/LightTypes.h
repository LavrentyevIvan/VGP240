#pragma once
#include "Light.h"

class DirectionalLight : public Light
{
public:
	virtual X::Color ComputeLightColor(const Vector3& position, const Vector3& normal) const override;

	void SetDirection(const Vector3& direction);
private:
	Vector3 mDirection;

};

class PointLight : public Light
{
public:
	virtual X::Color ComputeLightColor(const Vector3& position, const Vector3& normal) const override;

	void SetPosition(const Vector3& direction);
	void SetAttenuation(float constant, float linear, float quadratic);
private:
	Vector3 mPosition;
	float mAttenConst = -1.0f;
	float mAttenLinear = 0.0f;
	float mAttenQuad = 0.0f;

};

class SpotLight : public Light
{
public:
	virtual X::Color ComputeLightColor(const Vector3& position, const Vector3& normal) const override;

	void SetPosition(const Vector3& position);
	void SetDirection(const Vector3& direction);
	void SetAttenuation(float constant, float linear, float quadratic);
	void SetAngle(float angle);
	void SetDecay(float decay);
private:
	Vector3 mPosition;
	Vector3 mDirection;
	float mAttenConst = -1.0f;
	float mAttenLinear = 0.0f;
	float mAttenQuad = 0.0f;
	float mCosAngle = cos(X::Math::kPiByTwo);
	float mDecay = 0.0f;

};