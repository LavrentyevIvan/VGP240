#include "MaterialManager.h"

MaterialManager* MaterialManager::Get()
{
	static MaterialManager sInstance;
	return &sInstance;
}

void MaterialManager::OnNewFrame()
{
	mAmbient = X::Colors::White;
	mDiffuse = X::Colors::White;
	mSpecular = X::Colors::White;
	mEmissive = X::Colors::Black;
	mShininess = 1.0f;
}

void MaterialManager::SetMaterialAmbient(const X::Color& color)
{
	mAmbient = color;
}

void MaterialManager::SetMaterialDiffuse(const X::Color& color)
{
	mDiffuse = color;
}

void MaterialManager::SetMaterialSpecular(const X::Color& color)
{
	mSpecular = color;

}

void MaterialManager::SetMaterialEmissive(float shininess)
{
	mEmissive = shininess;
}

const X::Color& MaterialManager::GetMaterialAmbient() const
{
	return mAmbient;
}

const X::Color& MaterialManager::GetMaterialDiffuse() const
{
	return mDiffuse;

}

const X::Color& MaterialManager::GetMaterialSpecular() const
{
	return mSpecular;

}

const X::Color& MaterialManager::GetMaterialEmissive() const
{
	return mEmissive;
}

float MaterialManager::GetMaterialShininess() const
{
	return mShininess;
}
