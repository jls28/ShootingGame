#include "DXUT.h"
#include "ImageManager.h"

#include "SingleTexture.h"
#include "MultiTexture.h"

ImageManager::ImageManager()
{
	D3DXCreateSprite(g_pDevice, &m_pSprite);
}


ImageManager::~ImageManager()
{
	ImageClear();

	SAFE_RELEASE(m_pSprite);

	m_systemLog.clear();
}

Texture* ImageManager::AddImage(const string & key, const string & path, int count)
{
	auto find = m_mapTexture.find(key);

	if (find == m_mapTexture.end())
	{
		Texture* tex;

		if (count == 0)
			tex = new SingleTexture;
		else
			tex = new MultiTexture;

		tex->AddImage(path, count);

		m_mapTexture.insert(make_pair(key, tex));

		return tex;
	}

	return find->second;
}

Texture* ImageManager::GetImage(const string & key, int count)
{
	auto find = m_mapTexture.find(key);

	if (find != m_mapTexture.end())
	{
		return find->second->GetImage(count);
	}

	return nullptr;
}

void ImageManager::LostDevice()
{
	m_pSprite->OnLostDevice();
}

void ImageManager::ResetDevice()
{
	m_pSprite->OnResetDevice();
}

void ImageManager::Begin(bool isInterface)
{
	if (isInterface)
		m_pSprite->Begin(D3DXSPRITE_ALPHABLEND);
	else
		m_pSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_OBJECTSPACE);
}

void ImageManager::End()
{
	m_pSprite->End();
}

void ImageManager::Render(Texture * texture, Vector3 position, Vector3 scale, float rot, DWORD color)
{
	if (!texture->texturePtr) return;

	Matrix S, R, T;

	D3DXMatrixScaling(&S, scale.x, scale.y, scale.z);
	D3DXMatrixRotationZ(&R, D3DXToRadian(rot));
	D3DXMatrixTranslation(&T, position.x, position.y, position.z);

	Matrix W = S * R * T;

	m_pSprite->SetTransform(&W);

	Vector3 C(texture->info.Width / 2, texture->info.Height / 2, 0);

	m_pSprite->Draw(texture->texturePtr, NULL, &C, NULL, color);
}

void ImageManager::CenterRender(Texture * texture, Vector3 position, Vector3 scale, Vector3 center, float rot, DWORD color)
{
	if (!texture->texturePtr) return;

	Matrix S, R, T;

	D3DXMatrixScaling(&S, scale.x, scale.y, scale.z);
	D3DXMatrixRotationZ(&R, D3DXToRadian(rot));
	D3DXMatrixTranslation(&T, position.x, position.y, position.z);

	Matrix W = S * R * T;

	m_pSprite->SetTransform(&W);

	m_pSprite->Draw(texture->texturePtr, NULL, &center, NULL, color);
}

void ImageManager::CropRender(Texture * texture, Vector3 position, const RECT & rcRange)
{
	if (!texture->texturePtr) return;

	Matrix W;
	D3DXMatrixTranslation(&W, position.x, position.y, position.z);

	m_pSprite->SetTransform(&W);

	m_pSprite->Draw(texture->texturePtr, &rcRange,
		&(Vector3(texture->info.Width / 2, texture->info.Height / 2, 0)), NULL, 0xffffffff);
}

void ImageManager::CropCenterRender(Texture * texture, Vector3 position, Vector3 scale, Vector3 center, const RECT & rcRange)
{
	if (!texture->texturePtr) return;

	Matrix S, R, T;

	D3DXMatrixScaling(&S, scale.x, scale.y, scale.z);
	D3DXMatrixTranslation(&T, position.x, position.y, position.z);

	Matrix W = S * T;
	m_pSprite->SetTransform(&W);

	m_pSprite->Draw(texture->texturePtr, &rcRange,
		&center, NULL, 0xffffffff);
}

void ImageManager::PrintCenterText(const string & cont, Vector3 position, int size, DWORD color)
{
	LPD3DXFONT lpFont;
	D3DXMATRIX mat;

	D3DXCreateFontA(g_pDevice, size, 0, 0, 1, false, HANGUL_CHARSET, 0, 0, 0, "Fixedsys", &lpFont);

	D3DXMatrixTranslation(&mat,
		position.x - size * (cont.size() * 0.25), position.y - size / 2.f, 0);

	m_pSprite->SetTransform(&mat);
	lpFont->DrawTextA(m_pSprite, cont.c_str(), cont.size(), NULL, DT_NOCLIP | DT_CENTER, color);
	SAFE_RELEASE(lpFont);
}


void ImageManager::PrintText(const string & cont, Vector3 position, int size, DWORD color)
{
	LPD3DXFONT lpFont;
	D3DXMATRIX mat;

	D3DXCreateFontA(g_pDevice, size, 0, 0, 1, false, HANGUL_CHARSET, 0, 0, 0, "Fixedsys", &lpFont);

	D3DXMatrixTranslation(&mat,	position.x, position.y, 0);

	m_pSprite->SetTransform(&mat);
	lpFont->DrawTextA(m_pSprite, cont.c_str(), cont.size(), NULL, DT_NOCLIP | DT_CENTER, color);
	SAFE_RELEASE(lpFont);
}

void ImageManager::PrintLog(const string & cont, D3DCOLORVALUE color)
{
	m_systemLog.push_back(make_pair(cont, color));
}

void ImageManager::DrawLine(Vector2 * vecList, int count, float width, bool bIsAntialias, D3DCOLOR color)
{
	ID3DXLine* ILine;

	D3DXCreateLine(DXUTGetD3D9Device(), &ILine);

	//	if (renderType == SCROLL)
	//	for (int i = 0; i < count; i++) vecList[i] -= Vector2(CAMERA.GetPosition() - V3CENTER);

	ILine->SetWidth(width);
	ILine->SetAntialias(bIsAntialias);
	ILine->Begin();

	ILine->Draw(vecList, count, color);

	ILine->End();
	SAFE_RELEASE(ILine);
}

void ImageManager::DrawTransformLine(Vector2 * vecList, int count, float width, bool bIsAntialias, D3DCOLOR color)
{
	ID3DXLine* ILine;

	D3DXCreateLine(DXUTGetD3D9Device(), &ILine);

	for (int i = 0; i < count; i++)
		vecList[i] -= Vector2(CAMERA.GetPosition() - V3CENTER);

	ILine->SetWidth(width);
	ILine->SetAntialias(bIsAntialias);
	ILine->Begin();

	ILine->Draw(vecList, count, color);

	ILine->End();
	SAFE_RELEASE(ILine);
}

void ImageManager::ImageClear()
{
	for (auto iter : m_mapTexture)
		SAFE_DELETE(iter.second);

	m_mapTexture.clear();
}

void ImageManager::UpdateSystemLog()
{
	for (auto iter = m_systemLog.begin(); iter != m_systemLog.end(); )
	{
		if (iter->second.a <= 30)
		{
			iter = m_systemLog.erase(iter);
		}
		else
		{
			iter->second.a -= GetDeltaTime() * 100;
			iter++;
		}
	}
}

void ImageManager::RenderSystemLog()
{
	int offsetY = 200 - m_systemLog.size() * 60;

	Begin(true);

	for (auto iter : m_systemLog)
	{
		PrintCenterText(iter.first, Vector3(WINSIZEX / 2, offsetY, 0), 60,
			D3DCOLOR_ARGB((int)iter.second.a, (int)iter.second.r, (int)iter.second.g, (int)iter.second.b));
		offsetY += 60;
	}

	End();
}
