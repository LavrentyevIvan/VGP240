#include "CmdDrawPixel.h"

#include "Rasterizer.h"

bool CmdDrawPixel::Execute(const std::vector<std::string>& params)
{
	// Need at least 2 params for x, y
	if (params.size() < 2)
		return false;

	int positionX = stoi(params[0]);
	int positionY = stoi(params[1]);

	// Draw the pixel
	Rasterizer::Get()->DrawPoint(positionX, positionY);
	return true;
}
