#pragma once

#include <iostream>

#include <string>
#include <map>
#include <random>
#include <list>
#include <vector>
#include <functional>
#include <algorithm>
#include <thread>

using namespace std;

#define WINSIZEX 1280
#define WINSIZEY 720
#define WINMODE  false

#define GetNowTime()	timeGetTime()
#define GetDeltaTime()	DXUTGetElapsedTime()
#define g_pDevice		DXUTGetD3D9Device()
#define g_pHWND			DXUTGetHWND()

#define SAFE_DESTROY(p) {if(p) {(p)->Destroy(); delete (p); (p) = nullptr; }}
#define SAFE_DESTROY_AUTO(p) {if(p) {(p)->AutoManaged_Destroy(); (p)->Destroy(); delete (p); (p) = nullptr; }}
#define SAFE_KILL(p) {if(p) { (p)->Kill(); (p) = nullptr; }}

#define CONSOLE_LOG(log) { std::cout << log << std::endl; }
#define MESSAGE_LOG(log) MessageBoxA(g_pHWND, log, "[ log ]", MB_OK);

#define V3ZERO		Vector3(0, 0, 0)
#define V3CENTER	Vector3(WINSIZEX / 2, WINSIZEY / 2, 0)

typedef D3DXVECTOR2 Vector2;
typedef D3DXVECTOR3 Vector3;
typedef D3DXVECTOR4 Vector4;

typedef D3DXMATRIX	Matrix;
typedef DWORD		Color;

typedef LPDIRECT3DTEXTURE9 lpTexture9;
typedef D3DXIMAGE_INFO TextureInfo;

template <typename T>
void Lerp(T* p, const T& s, const T& e, float sp)
{
	*p = s + (e - s) * sp;
}

#include "ImageManager.h"
#include "InputManager.h"
#include "CollisionManager.h"
#include "CameraManager.h"
#include "ObjectManager.h"
#include "SceneManager.h"
#include "SoundManager.h"
#include "DataManager.h"

#include "Collider.h"