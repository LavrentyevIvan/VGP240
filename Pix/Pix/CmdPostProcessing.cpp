#include "CmdPostProcessing.h"
#include "PostProcessing.h"

bool CmdPostProcessingBeginDraw::Execute(const std::vector<std::string>& params)
{
	PostProcessing::Get()->BeginDraw();
	return true;
}
bool CmdPostProcessingEndDraw::Execute(const std::vector<std::string>& params)
{
	PostProcessing::Get()->EndDraw();
	return true;
}
bool CmdPostProcessingSetEffectType::Execute(const std::vector<std::string>& params)
{
	EffectType effectType = EffectType::None;
	if (params[0] == "none")
	{
		effectType = EffectType::None;
	}
	else if (params[0] == "monochrome")
	{
		effectType = EffectType::MonoChrome;
	}
	else if (params[0] == "invert")
	{
		effectType = EffectType::Invert;
	}
	else if (params[0] == "blur")
	{
		effectType = EffectType::Blur;
	}
	else if (params[0] == "colormaskr")
	{
		effectType = EffectType::ColorMaskR;
	}
	else if (params[0] == "colormaskb")
	{
		effectType = EffectType::ColorMaskB;
	}
	else if (params[0] == "colormaskg")
	{
		effectType = EffectType::ColorMaskG;
	}
	else if (params[0] == "sepia")
	{
		effectType = EffectType::Sepia;
	}
	else if (params[0] == "wave")
	{
		effectType = EffectType::Wave;
	}
	else
	{
		return false;
	}

	PostProcessing::Get()->SetEffectType(effectType);
	return true;
	
}
