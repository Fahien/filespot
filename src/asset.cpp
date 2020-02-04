#include <string>

#include "spot/file/asset.h"

namespace spot::file
{


AssetManager AssetManager::assets{};

AssetManager Asset::kManager{};


void Asset::init( AAssetManager* m )
{
	kManager.manager = m;
}


bool Asset::exists( const std::string& name )
{
	Asset asset{ name };
	return asset.file != nullptr;
}


Asset::Asset( AAsset* file )
:	file   { file }
,	length { 0 }
,	content{ nullptr }
{}


Asset::Asset( const std::string& name )
:	file{ AAssetManager_open( kManager.manager, name.c_str(), AASSET_MODE_BUFFER ) }
,	length { 0 }
,	content{ nullptr }
{}


size_t& Asset::get_length()
{
	if ( !content )
	{
		length = static_cast<size_t>( AAsset_getLength( file ) );
	}
	return length;
}


char* Asset::get_content()
{
	if ( !content )
	{
		get_length();
		content = std::unique_ptr<char[]>(new char[length + 1]);
		AAsset_read(file, content.get(), length);
		content.get()[length] = '\0';
	}
	return content.get();
}


AssetManager::AssetManager()
:	manager{ nullptr }
{}


void AssetManager::init( AAssetManager* assets )
{
	manager = assets;
}


void AssetManager::init( JNIEnv* env, jobject assets )
{
	manager = AAssetManager_fromJava( env, assets );
}


} // namespace spot::file
