#ifndef FST_ASSET_H_
#define FST_ASSET_H_

#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>
#include <memory>
#include <stdexcept>


namespace filespot
{

class AssetException : public std::runtime_error
{
  public:
	AssetException(const std::string& msg)
	:	std::runtime_error(msg)
	{}
};


class AssetManager;


class Asset
{
  public:
	static void Init(AAssetManager* pManager);
	static bool Exists(const std::string& name);

	Asset(AAsset* file);
	Asset(const std::string& name);

	/// Returns the content as c string
	char* GetContent();

	/// Returns the length of the string
	size_t& GetLength();

  private:
	static AssetManager kManager;

	/// Handle to the file (no need to release it)
	AAsset* mFile;

	/// Length in byte
	size_t mLength;

	/// Content interpreted as c string
	std::unique_ptr<char[]> mContent;
};


class AssetManager
{
  public:
	static AssetManager assets;

	void Init(AAssetManager* assets);
	void Init(JNIEnv* env, jobject assets);

  private:
	AssetManager();

	/// Android asset manager
	AAssetManager* mManager;

	friend class Asset;
};

}


#endif // FST_ASSET_H_
