#include "CmdSetResolution.h"

#include <XEngine.h>

float gResolutionX = 0.0f;
float gResolutionY = 0.0f;

bool CmdSetResolution::Execute(const std::vector<std::string>& params)
{
	// Need at least 2 params for width, height
	if (params.size() < 2)
		return false;

	const int width = stoi(params[0]);
	const int height = stoi(params[1]);

	// Optional third param for pixel size
	const int pixelSize = params.size() > 2 ? stoi(params[2]) : 1;

	// Optional fourth param for show grid
	const bool showGrid = params.size() > 3 && params[3] == "true";

	// Cache resolution
	gResolutionX = (float)width;
	gResolutionY = (float)height;

	X::InitRenderTexture(width, height, pixelSize);

	if (showGrid && pixelSize > 1)
		X::DrawScreenGrid(pixelSize, X::Colors::DarkGray);

	return true;
}
