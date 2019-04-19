#pragma once
#include "Frame.h"

enum RENDERMODE
{
	RENDERMODE_NONE	= 1 << 0,
	RENDERMODE_FRAME = 1 << 1,
	RENDERMODE_MULTIPLY = 1 << 2
};

class Frame;
class Collider;
class GameObject
{
private:

	// GENERIC
	bool m_deleteTrigger = false;
	bool m_autoManaged = true;

protected:
	// TRANSFORM

	Vector3 m_position = Vector3(0.0f, 0.0f, 0.0f);
	Vector3 m_scale = Vector3(1.0f, 1.0f, 1.0f);
	Vector3 m_center;

	Color	m_color = 0xffffffff;

	string  m_tag;

	float m_rotation = 0.0f;

	OBJKIND m_objectKind;

	// RENDERER

	Texture* m_texture = nullptr;
	Frame m_frame;

	INT m_renderLayer = 0;
	INT m_renderFlip = 1;
	INT m_renderMode = RENDERMODE_FRAME;
	INT m_renderType = SCROLL;

	// COLLISION

	Collider* m_collider = nullptr;

public:
	GameObject(OBJKIND kind);
	virtual ~GameObject();

	virtual void Init() {}
	virtual void Update() {}
	virtual void Render() {}
	virtual void Destroy() {}

	virtual void OnCollision(Collider* col) {}

	void UseCollider(float range);
	void UseCollider(float width, float height);
	void UseCollider(float left, float top, float right, float bottom);

	void UseFrame(int start, int end, float delay);
	void UseCenter(Texture* texture);

	void Kill() { m_deleteTrigger = true; }
	void Kill(GameObject* obj) { if(obj) obj->Kill(); }
	bool IsDead() { return m_deleteTrigger; }

public:

	// AUTO MANAGED LOOP

	void AutoManaged_Init();
	void AutoManaged_Update();
	void AutoManaged_Render();
	void AutoManaged_Destroy();

public:
	// GET, SET FUNCTIONS 

	Vector3 GetPosition() { return m_position; }		void SetPosition(Vector3 pos) { m_position = pos; }
	void SetPosition(float x, float y, float z = 0) { m_position.x = x; m_position.y = y; m_position.z = z; }
	Vector3 GetScale() { return  m_scale; }			void SetScale(Vector3 sca) { m_scale = sca; }
	void SetScale(float x, float y, float z = 0) { m_scale.x = x; m_scale.y = y; m_scale.z = z; }
	Vector3 GetCenter() { return  m_center; }			void SetCenter(Vector3 cen) { m_center = cen; }
	Color	GetColor() { return  m_color; }			void SetColor(Color clr) { m_color = clr; }
	void SetColor(int a, int r, int g, int b) { m_color = D3DCOLOR_ARGB(a, r, g, b); }
	string	GetTag() { return  m_tag; }				void SetTag(string tg) { m_tag = tg; }
	float	GetRotation() { return  m_rotation; }		void SetRotation(float rot) { m_rotation = rot; }
	float GetRotation(Vector3 dir);
	OBJKIND GetKind() { return m_objectKind; }

	Texture* GetTexture() { return  m_texture; }		void SetTexture(Texture* tex) { m_texture = tex; }
	void SetTexture(const string& strTex, int count = -1) { SetTexture(IMAGE.GetImage(strTex, count)); }
	INT		GetRenderLayer() { return  m_renderLayer; } void SetRenderLayer(INT layer) { m_renderLayer = layer; }
	INT		GetRenderFlip() { return  m_renderFlip; }	void SetRenderFlip(INT flp) { m_renderFlip = flp; }
	INT		GetRenderMode() { return m_renderMode; }	void SetRenderMode(INT mod) { m_renderMode = mod; }
	INT		GetRenderType() { return m_renderType; }	void SetRenderType(INT typ) { m_renderType = typ; }

	Collider* GetCollider() { return m_collider; }		void SetCollider(Collider* col) { m_collider = col; }

	bool	GetAutoManaged() { return m_autoManaged; }	void SetAutoManaged(bool aut) { m_autoManaged = aut; }

public:
	// PROPERTY MEMBERS

	__declspec(property(get = GetPosition, put = SetPosition))		Vector3		position;
	__declspec(property(get = GetScale, put = SetScale))		Vector3		scale;
	__declspec(property(get = GetCenter, put = SetCenter))		Vector3		center;
	__declspec(property(get = GetColor, put = SetColor))		Color		color;
	__declspec(property(get = GetTag, put = SetTag))		string		tag;
	__declspec(property(get = GetRotation, put = SetRotation))		float		rotation;
	__declspec(property(get = GetKind))									OBJKIND		objectKind;

	__declspec(property(get = GetTexture, put = SetTexture))		Texture*	texture;
	__declspec(property(get = GetRenderLayer, put = SetRenderLayer))	INT			renderLayer;
	__declspec(property(get = GetRenderFlip, put = SetRenderFlip))		INT			renderFlip;
	__declspec(property(get = GetRenderMode, put = SetRenderMode))		INT			renderMode;
	__declspec(property(get = GetRenderType, put = SetRenderType))		INT			renderType;

	__declspec(property(get = GetCollider, put = SetCollider))		Collider*	collider;

	__declspec(property(get = GetAutoManaged, put = SetAutoManaged))	bool		autoManaged;

public:
	// SORTING FUNCTIONS

	static bool CompareLayer(GameObject* f, GameObject* s)
	{
		return f->renderLayer < s->renderLayer;
	}

	static bool CompareY(GameObject* f, GameObject* s)
	{
		if (f->renderLayer == s->renderLayer)
			return f->position.y < s->position.y;
		else
			return false;
	}

public:
	// FIND FUNCTIONS

	static GameObject* FindGameObjectWithTag(const string& tag);

	public:
		// CREATE FUNCTIONS

	static GameObject* CreateBackGround(const string& name, int layer)
	{
		auto map = Instantiate(GameObject(OBJ_BACKGROUND));

		map->SetTexture(name);
		map->UseCenter(map->texture);
		map->position = map->center;
		map->renderLayer = layer;

		return map;
	}

	static const int obstacleLayer = 1;

	static GameObject* CreateObstacle(Vector3 position, const string& key, int imgCount = -1)
	{
		auto obstacle = Instantiate(GameObject(OBJ_BACKGROUND));

		obstacle->SetTexture(key, imgCount);
		obstacle->UseCenter(obstacle->texture);

		obstacle->position = position + obstacle->center;
		obstacle->renderLayer = obstacleLayer;

		return obstacle;
	}

	static GameObject* CreateLayerObstacle(Vector3 position, const string& key, int layer)
	{
		auto obstacle = Instantiate(GameObject(OBJ_BACKGROUND));

		obstacle->SetTexture(key, -1);
		obstacle->UseCenter(obstacle->texture);

		obstacle->position = position + obstacle->center;
		obstacle->renderLayer = layer;

		return obstacle;
	}
};