#pragma once
#include <XEngine.h>
#include "Light.h"

class LightManager
{
public:
	static LightManager* Get();

	void OnNewFrame();
	void SetLightingAmbient(const X::Color& color);
	void SetLightingDiffuse(const X::Color& color);
	void SetLightingSpecular(const X::Color& color);

	void AddDirectionalLight(const Vector3& direciton);

	X::Color ComputeLightColor(const Vector3& position, const Vector3& normal) const;

private:
	std::vector<std::unique_ptr<Light>> mLights;
	X::Color mAmbient = X::Colors::White;
	X::Color mDiffuse = X::Colors::White;
	X::Color mSpecular = X::Colors::White;
};