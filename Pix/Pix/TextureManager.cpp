#include "TextureManager.h"

TextureManager* TextureManager::Get()
{
	static TextureManager sInstance;
	return &sInstance;
}


void TextureManager::Clear()
{
	mTextures.clear();
	mCurrentTexture = nullptr;
}

void TextureManager::SetTexture(const std::string& fileName)
{
	auto iter = std::find_if(mTextures.begin(), mTextures.end(),
		[fileName](auto& texture)
		{
			return texture->GetFileName() == fileName;
		});
	if (iter != mTextures.end())
	{
		mCurrentTexture = iter->get();
	}
	else
	{
		auto& texture = mTextures.emplace_back(std::make_unique<Texture>());
		texture->Load(fileName);
		mCurrentTexture = texture.get();
	}
}

void TextureManager::SetAddressMode(AddressMode mode)
{
	mAddressMode = mode;

}

void TextureManager::SetUseFilter(bool useFilter)
{
	mUseFilter = useFilter;
}

X::Color TextureManager::SampleColor(const X::Color& uv) const
{
	X::Color color = uv;
	if (mCurrentTexture != nullptr && uv.z < 0.0f)
	{
		float u = uv.x / uv.w;
		float v = uv.y / uv.w;

		color = mCurrentTexture->GetPixel(u, v, mAddressMode, mUseFilter);
	}
	return color;
}