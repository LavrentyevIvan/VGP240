#include "Viewport.h"

#include <XEngine.h>

Viewport* Viewport::Get()
{
	static Viewport sInstance;
	return &sInstance;
}

void Viewport::OnNewFrame()
{
	*this = {};
}

void Viewport::DrawViewport()
{
	if (mShowViewport)
		X::DrawScreenRect({ mPosX, mPosY, mPosX + mWidth, mPosY + mHeight }, X::Colors::White);
}

void Viewport::SetViewport(float x, float y, float width, float height)
{
	mPosX = X::Math::Max(x, 0.0f);
	mPosY = X::Math::Max(y, 0.0f);
	mWidth = X::Math::Max(width, 0.0f);
	mHeight = X::Math::Max(height, 0.0f);
}