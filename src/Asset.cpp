#include <string>

#include "filespot/Asset.h"

using namespace filespot;


AssetManager AssetManager::assets{};

AssetManager Asset::kManager{};


void Asset::Init(AAssetManager* pManager)
{
	kManager.mManager = pManager;
}


bool Asset::Exists(const std::string& name)
{
	Asset asset{ name };
	return asset.mFile != nullptr;
}


Asset::Asset(AAsset* file)
:	mFile   { file }
,	mLength { 0 }
,	mContent{ nullptr }
{}


Asset::Asset(const std::string& name)
:	mFile{ AAssetManager_open(kManager.mManager, name.c_str(), AASSET_MODE_BUFFER) }
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
:	mManager{ nullptr }
{}


void AssetManager::Init(AAssetManager* assets)
{
	mManager = assets;
}


void AssetManager::Init(JNIEnv* env, jobject assets)
{
	mManager = AAssetManager_fromJava(env, assets);
}
