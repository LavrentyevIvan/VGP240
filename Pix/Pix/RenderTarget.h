#pragma once

#include <XEngine.h>

class RenderTarget
{
public:
	void Initialize(int width, int height, const X::Color& clearColor = X::Colors::Black);
	void ClearImage(const X::Color& clearColor);
	void DrawPixel(int x, int y, const X::Color& color);
	const X::Color& GetColor(int x, int y) const;

	int GetWidth() { return mWidth; }
	int GetHeight() { return mHeight; }

private:
	int mWidth = 0;
	int mHeight = 0;
	std::unique_ptr<X::Color[]> mRenderPixels;
};