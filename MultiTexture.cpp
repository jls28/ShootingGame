#include "DXUT.h"
#include "MultiTexture.h"
#include "SingleTexture.h"

MultiTexture::MultiTexture()
{
}


MultiTexture::~MultiTexture()
{
	for (auto iter : vecTexture)
		SAFE_DELETE(iter);
}

Texture * MultiTexture::GetImage(int count)
{
	if (count == -1)
		return this;
	else
		return vecTexture[count];
}

void MultiTexture::AddImage(const string & path, int count)
{
	char sz[128] = "";

	for (int i = 1; i <= count; i++)
	{
		sprintf(sz, path.c_str(), i);

		Texture* texture = new SingleTexture();
		texture->AddImage(sz);

		vecTexture.push_back(texture);
	}
}

int MultiTexture::size()
{
	return vecTexture.size();
}
