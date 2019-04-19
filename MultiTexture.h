#pragma once
#include "Texture.h"

class SingleTexture;
class MultiTexture :
	public Texture
{
private:
	vector<Texture*> vecTexture;
public:
	MultiTexture();
	virtual ~MultiTexture();

	virtual Texture* GetImage(int count = -1) override;
	virtual void AddImage(const string& path, int count = 0) override;

	virtual int size() override;
};

