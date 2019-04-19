#include "DXUT.h"
#include "SingleTexture.h"


SingleTexture::SingleTexture()
{
}


SingleTexture::~SingleTexture()
{
	SAFE_RELEASE(texturePtr);
}

Texture * SingleTexture::GetImage(int count)
{
	return this;
}

void SingleTexture::AddImage(const string & path, int count)
{
	D3DXCreateTextureFromFileExA(g_pDevice, path.c_str(), D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT_NONPOW2, 0,
		0, D3DFMT_UNKNOWN, D3DPOOL_MANAGED, D3DX_DEFAULT, D3DX_DEFAULT, D3DCOLOR_XRGB(10, 10, 10), &info, 0, &texturePtr);
}

int SingleTexture::size()
{
	return 1;
}
