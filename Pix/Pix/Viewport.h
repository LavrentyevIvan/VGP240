#pragma once

class Viewport
{
public:
	static Viewport* Get();

public:
	void OnNewFrame();

	void DrawViewport();

	void SetViewport(float x, float y, float width, float height);
	void ShowViewport(bool show) { mShowViewport = show; }

	float GetMinX() const { return mPosX; }
	float GetMaxX() const { return mPosX + mWidth; }
	float GetMinY() const { return mPosY; }
	float GetMaxY() const { return mPosY + mHeight; }

private:
	float mPosX = 0.0f;
	float mPosY = 0.0f;
	float mWidth = 0.0f;
	float mHeight = 0.0f;
	bool mShowViewport = false;
	bool mClipping = false;
};