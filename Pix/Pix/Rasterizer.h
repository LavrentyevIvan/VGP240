#pragma once

#include <XEngine.h>

class Rasterizer
{
public:
	static Rasterizer* Get();

public:
	void SetColor(X::Color color);

	void DrawPoint(int x, int y);

private:
	X::Color mColor = X::Colors::White;
};