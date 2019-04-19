#pragma once
#include "GameObject.h"
class ImageLoader :
	public GameObject
{
public:
	struct LOAD_INFO
	{
		string key, path;
		int count;
		LOAD_INFO(const string& key, const string& path, int count = 0) : key(key), path(path), count(count) {}
	};

	vector<LOAD_INFO> loader;
	int curImage;
	int maxImage;

	std::function<void()> endFunc;
	string sceneName;

	GameObject* gageBar;
	GameObject* backGround;

	bool isPlayBgm;

public:
	ImageLoader(bool isSoundPlay, function<void()> _endFunc);
	virtual ~ImageLoader();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Destroy() override;

	void Load(const string& key, const string& path, int count = 0);

private:

};

