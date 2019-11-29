#pragma once

#include <Hazel.h>
#include <Box2D/Box2D.h>
#include <vector>

#include "Body.h"
#include "Ship.h"
#include "Hazel/Camera/Camera.h"


struct LinkedListIterator
{
public:
	LinkedListIterator(b2Body* first) : m_Current(first) {}

	b2Body* operator* () { return m_Current; }
	b2Body* operator-> () { return m_Current; }

	LinkedListIterator& operator++ () { m_Current = m_Current->GetNext(); return *this; }
	LinkedListIterator operator++ (int) { const auto temp(*this); ++*this; return temp; }

	bool operator== (const LinkedListIterator& that) const { return m_Current == that.m_Current; }
	bool operator!= (const LinkedListIterator& that) const { return !(*this == that); }

	~LinkedListIterator() {}
private:
	b2Body* m_Current;

};


class World
{
public:
	World();

	struct Constants {
		static float G;
	};

	void Update();
	void Render();

	inline LinkedListIterator BodiesBegin() { return m_World->GetBodyList();  }
	inline LinkedListIterator BodiesEnd() { return nullptr; }

	inline b2World* GetWorld() { return m_World.get(); }

	static inline Body* ToBody(b2Body* body) { return reinterpret_cast<Body*>(body->GetUserData()); }

private:
	Hazel::Scope<b2World> m_World;
	Hazel::Camera2D m_Camera;
};

class WorldCameraController : public Hazel::CameraController2D
{
	friend class Camera2D;
	virtual void Update(Hazel::Camera2D& camera);
};


