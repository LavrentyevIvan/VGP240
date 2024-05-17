#include "CmdPopMatrix.h"
#include "MatrixStack.h"


bool CmdPopMatrix::Execute(const std::vector<std::string>& params)
{
	MatrixStack::Get()->PopMatrix();
	return true;
}
