#pragma once
class Texture
{
public:
	lpTexture9 texturePtr;
	TextureInfo info;
public:
	Texture();
	virtual ~Texture();

	virtual void AddImage(const string& path, int count = 0) PURE;
	virtual Texture* GetImage(int count = -1) PURE;

	virtual int size() PURE;
};

