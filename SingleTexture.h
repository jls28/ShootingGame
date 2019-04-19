#pragma once
#include "Texture.h"
class SingleTexture :
	public Texture
{
public:
	SingleTexture();
	virtual ~SingleTexture();

	virtual Texture* GetImage(int count = 0) override;
	virtual void AddImage(const string& path, int count = 0) override;

	virtual int size() override;
};

