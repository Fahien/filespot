#include <string>

#include "filespot/AssetManager.h"

using namespace filespot;


AssetManager AssetManager::assets{};


Asset::Asset(AAsset* file)
:	mFile   { file }
,	mLength { 0 }
,	mContent{ nullptr }
{}


size_t& Asset::GetLength()
{
	if (!mContent)
	{
		mLength = static_cast<size_t>(AAsset_getLength(mFile));
	}
	return mLength;
}


char* Asset::GetContent()
{
	if (!mContent)
	{
		GetLength();
		mContent = std::unique_ptr<char[]>(new char[mLength + 1]);
		AAsset_read(mFile, mContent.get(), mLength);
		mContent.get()[mLength] = '\0';
	}
	return mContent.get();
}


AssetManager::AssetManager()
:	mAssets{ nullptr }
{}


void AssetManager::Init(AAssetManager* assets)
{
	mAssets = assets;
}


void AssetManager::Init(JNIEnv* env, jobject assets)
{
	mAssets = AAssetManager_fromJava(env, assets);
}


Asset AssetManager::Open(const std::string& name) const
{
	if (!mAssets)
	{
		throw AssetException{ "AssetManager instance is not initialized" };
	}

	AAsset* file{ AAssetManager_open(mAssets, name.c_str(), AASSET_MODE_BUFFER) };
	if (!file)
	{
		throw AssetException{ "Could not open a file: " + name };
	}

	return Asset{ file };
}
