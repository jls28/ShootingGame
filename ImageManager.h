#pragma once
#include "Singleton.h"

enum RENDERTYPE
{
	SCREEN,
	SCROLL
};

class Texture;
class ImageManager :
	public Singleton<ImageManager>
{
private:
	LPD3DXSPRITE m_pSprite;
	map<string, Texture*> m_mapTexture;

	list<pair<string, D3DCOLORVALUE>> m_systemLog;
public:
	ImageManager();
	virtual ~ImageManager();

	Texture* AddImage(const string& key, const string& path, int count = 0);
	Texture* GetImage(const string& key, int count = -1);

	void LostDevice();
	void ResetDevice();

	void Begin(bool isInterface = false);
	void End();

	void Render(Texture* texture, Vector3 position, Vector3 scale, float rot = 0.0f, DWORD color = 0xffffffff);
	void CenterRender(Texture* texture, Vector3 position, Vector3 scale, Vector3 center, float rot = 0.0f, DWORD color = 0xffffffff);
	void CropRender(Texture* texture, Vector3 position, const RECT& rcRange);
	void CropCenterRender(Texture* texture, Vector3 position, Vector3 scale, Vector3 center, const RECT& rcRange);

	void PrintCenterText(const string& cont, Vector3 position, int size, DWORD color = 0xffffffff);
	void PrintText(const string& cont, Vector3 position, int size, DWORD color = 0xffffffff);
	void PrintLog(const string& cont, D3DCOLORVALUE color = { 255,255,255,255 });

	void DrawLine(Vector2* vecList, int count, float width, bool bIsAntialias, D3DCOLOR color = 0xffffffff);
	void DrawTransformLine(Vector2* vecList, int count, float width, bool bIsAntialias, D3DCOLOR color = 0xffffffff);

	void ImageClear();

	void UpdateSystemLog();
	void RenderSystemLog();
};

#define IMAGE (*ImageManager::Instance())