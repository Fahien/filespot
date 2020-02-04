#pragma once

#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>
#include <memory>
#include <stdexcept>


namespace spot::file
{

class AssetException : public std::runtime_error
{
  public:
	AssetException( const std::string& msg )
	:	std::runtime_error( msg )
	{}
};


class AssetManager;


class Asset
{
  public:
	static void init( AAssetManager* pManager );
	static bool exists( const std::string& name );

	Asset( AAsset* file );
	Asset( const std::string& name );

	/// Returns the content as c string
	char* get_content();

	/// Returns the length of the string
	size_t& get_length();

  private:
	static AssetManager kManager;

	/// Handle to the file (no need to release it)
	AAsset* file;

	/// Length in byte
	size_t length;

	/// Content interpreted as c string
	std::unique_ptr<char[]> content;
};


class AssetManager
{
  public:
	static AssetManager assets;

	void init( AAssetManager* assets );
	void init( JNIEnv* env, jobject assets );

  private:
	AssetManager();

	/// Android asset manager
	AAssetManager* manager;

	friend class Asset;
};

}
