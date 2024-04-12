#include "Graphics.h"

#include "Viewport.h"

void Graphics::NewFrame()
{
	Viewport::Get()->OnNewFrame();
}