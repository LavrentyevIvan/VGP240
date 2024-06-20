#include "PostProcessing.h"

PostProcessing* PostProcessing::Get()
{
	static PostProcessing sInstance;
	return &sInstance;
}

void PostProcessing::Initialize(int width, int height, const X::Color& clearColor)
{
	mClearColor = clearColor;
	mRenderTarget.Initialize(width, height, clearColor);
}

void PostProcessing::OnNewFrame()
{
	mDrawBegin = false;
	mEffectType = EffectType::None;
}

void PostProcessing::SetEffectType(EffectType effectType)
{
	mEffectType = effectType;
}

void PostProcessing::BeginDraw()
{
	mDrawBegin = (mEffectType != EffectType::None);
	if (mDrawBegin)
	{
		mRenderTarget.ClearImage(mClearColor);
	}
}

bool PostProcessing::DrawToRenderTarget(int x, int y, const X::Color& color)
{
	if (mDrawBegin)
	{
		mRenderTarget.DrawPixel(x, y, color);
		return true;
	}
	return false;
}

void PostProcessing::EndDraw()
{
	if (mDrawBegin)
	{
		for (int y = 0; y < mRenderTarget.GetHeight(); ++y)
		{
			for (int x = 0; x < mRenderTarget.GetWidth(); ++x)
			{
				DrawPixel(x, y);
			}
		}
	}
	mDrawBegin = false;
}

void PostProcessing::DrawPixel(int x, int y)
{
	X::Color color = X::Colors::Black;
	// post processing
	switch (mEffectType)
	{
	case EffectType::None:
	{
		color = mRenderTarget.GetColor(x, y);
	}
	break;
	case EffectType::MonoChrome:
	{
		color = mRenderTarget.GetColor(x, y);
		color = (color.r + color.g + color.b) / 3.0f;
	}
	break;
	case EffectType::Invert:
	{
		color = mRenderTarget.GetColor(x, y);
		color.r = 1.0f - color.r;
		color.g = 1.0f - color.g;
		color.b = 1.0f - color.b;
	}
	break;
	case EffectType::Mirror:
	{
		color = mRenderTarget.GetColor(x, y);
		y = mRenderTarget.GetHeight() - y - 1;
	}
	break;
	case EffectType::Blur:
	{
		int offset = 2;
		color = mRenderTarget.GetColor(x, y)
			+ mRenderTarget.GetColor(x + offset, y)
			+ mRenderTarget.GetColor(x - offset, y)
			+ mRenderTarget.GetColor(x, y + offset)
			+ mRenderTarget.GetColor(x, y - offset)
			+ mRenderTarget.GetColor(x + offset, y + offset)
			+ mRenderTarget.GetColor(x + offset, y - offset)
			+ mRenderTarget.GetColor(x - offset, y + offset)
			+ mRenderTarget.GetColor(x - offset, y - offset);
		color /= 9.0f;
	}
	break;
	case EffectType::ColorMaskR:
	{
		color = mRenderTarget.GetColor(x, y);
		color.r = 0.0f;
	}
	break;
	case EffectType::ColorMaskG:
	{
		color = mRenderTarget.GetColor(x, y);
		color.g = 0.0f;
	}
	break;
	case EffectType::ColorMaskB:
	{
		color = mRenderTarget.GetColor(x, y);
		color.b = 0.0f;
	}
	break;
	case EffectType::Sepia:
	{
		color = mRenderTarget.GetColor(x, y);
		X::Math::Vector3 colorVec(color.r, color.g, color.b);
		color.r = X::Math::Dot(colorVec, X::Math::Vector3(0.393f, 0.769f, 0.189f));
		color.g = X::Math::Dot(colorVec, X::Math::Vector3(0.349f, 0.686f, 0.168f));
		color.b = X::Math::Dot(colorVec, X::Math::Vector3(0.272f, 0.534f, 0.131f));
	}
	break;
	case EffectType::Wave:
	{
		int yRippleLength = 50;
		color = mRenderTarget.GetColor(x, y);
		// 0 - 1
		float ratio = static_cast<float>(y % yRippleLength) / static_cast<float>(yRippleLength - 1);
		float circleValues = (ratio * 3.14159f);
		float sinRes = std::sin(circleValues);
		x += static_cast<int>(sinRes * 5.0f);
	}
	break;
	}
	X::DrawPixel(x, y, color);

}