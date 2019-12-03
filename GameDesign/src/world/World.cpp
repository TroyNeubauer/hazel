#include "World.h"
#include "ship/Ship.h"
#include "Planet.h"


double World::Constants::G = 6.67430E-11 * 10000000.0f;
Hazel::Ref<PartDef> Parts::MK1Capsule = nullptr;
Hazel::Ref<PartDef> Parts::FlyingShip = nullptr;
Hazel::Ref<PartDef> Parts::StaticShip = nullptr;

Hazel::TextureBuilder builder = Hazel::TextureBuilder::Default().NearestFiltering().ClampEdges();

World::World() : m_Camera(new WorldCameraController())
{
	m_World.reset(new b2World( {0.0f, 0.0f} ));//No gravity since we handle it ourselves
	Hazel::Ref<Hazel::Texture2D> RocketComponents = Hazel::Texture2D::Load("assets/textures/RocketComponents.png", builder);
	Hazel::Ref<Hazel::Texture2D> DefaultShip = Hazel::Texture2D::Load("assets/textures/Rocket.png", builder);

	Parts::MK1Capsule.reset(new PartDef{ "MK1 Capsule", 1.0f, 15.0f, Hazel::AnimationDef2D::Create(RocketComponents, { 0, 16 }, { 14, 16 }), 1.0f });
	Parts::FlyingShip.reset(new PartDef{ "Flying Ship", 1.5f, 15.0f, Hazel::AnimationDef2D::Create(DefaultShip, 0.2f, {25, 47}, {{0, 1}, {1, 1}, {2, 1}, {3, 1}, {4, 1}}), 2.0f });
	Parts::StaticShip.reset(new PartDef{ "Ship", 1.5f, 15.0f, Hazel::AnimationDef2D::Create(DefaultShip, {0, 0}, {25, 47}), 2.0f });

	m_Camera.SetPosition(vec2(0.0, 0.0));
	m_Camera.SetRotation(0.0f);
	m_Camera.SetZoom(10.0f);
}

void World::Update()
{
	m_Camera.Update();
	b2Body* body = m_World->GetBodyList();
	for (int i = 0; i < m_World->GetBodyCount(); i++, body = body->GetNext())
	{
		if (body->GetType() == b2_dynamicBody)
		{
			b2Body* other = m_World->GetBodyList();
			for (int j = 0; j < i; j++, other = other->GetNext())
			{
				b2Vec2 force = other->GetPosition() - body->GetPosition();
				double distance = force.Normalize();// Determine the amount of force to give
				force *= static_cast<float>((World::Constants::G * (double) body->GetMass() * (double) other->GetMass()) / (distance * distance));

				body->ApplyForceToCenter(force, true);
				other->ApplyForceToCenter(-force, true);
			}
		}
	}
	body = m_World->GetBodyList();
	for (int i = 0; i < m_World->GetBodyCount(); i++, body = body->GetNext())
	{
		Body* myBody = ToBody(body);
		myBody->Update(*this);
	}
	m_World->Step(Hazel::Engine::GetDeltaTime(), 10, 10);
	m_World->ClearForces();
}

void World::Render()
{
	Hazel::Renderer2D::BeginScene(m_Camera);
	for (auto it = BodiesBegin(); it != BodiesEnd(); it++)
	{
		Body* body = ToBody(*it);
		body->Render(*this);

	}
	Hazel::Renderer2D::EndScene();
}

Part& World::AddPart(b2Vec2 pos, const Hazel::Ref<PartDef>& partDef, float rot)
{
	Ship* ship = new Ship();
	m_Ships.push_back(Hazel::S(ship));
	Part& part = ship->GetParts().emplace_back(*this, pos, partDef);
	return part;
}

void World::Remove(Body* body)
{

	if(m_OnRemovedFunction)
		m_OnRemovedFunction(body);

	m_World->DestroyBody(body->GetBody());
	for (auto& it = m_Ships.begin(); it != m_Ships.end(); it++)
	{
		Ship* ship = it->get();
		for (auto& it2 = ship->GetParts().begin(); it2 != ship->GetParts().end(); it2++)
		{
			const Part& part = *it2;
			if (part.GetBody() == body->GetBody())
			{
				ship->GetParts().erase(it2);
				break;
			}
		}
		if (ship->GetParts().empty())
		{
			m_Ships.erase(it);
			break;
		}
	}

}


const float ACCEL_SPEED = 25.0f;

void WorldCameraController::Update(Hazel::Camera2D& camera)
{
	glm::vec2 move = { 0, 0 };
	glm::vec2 right = glm::rotate(glm::vec2(1.0f, 0.0f), glm::radians(camera.m_Rot));
	glm::vec2 up = glm::rotate(glm::vec2(0.0f, 1.0f), glm::radians(camera.m_Rot));
	bool moving = false;

	if (Hazel::Input::IsKeyPressed(HZ_KEY_W)) {
		move += up; moving = true;
	} if (Hazel::Input::IsKeyPressed(HZ_KEY_S)) {
		move -= up; moving = true;
	} if (Hazel::Input::IsKeyPressed(HZ_KEY_D)) {
		move += right; moving = true;
	} if (Hazel::Input::IsKeyPressed(HZ_KEY_A)) {
		move -= right; moving = true;
	}
	float length = move.length();
	if (length > 0.0f)
	{
		move /= length;
		move *= ACCEL_SPEED;
	}

	camera.m_ZoomVel -= Hazel::Input::GetScrollDelta() * 3.0f;

	camera.m_Vel += move * Hazel::Engine::GetDeltaTime();
	camera.m_Pos += camera.m_Vel * Hazel::Engine::GetDeltaTime();
	if (!moving)
	{
		camera.m_Vel *= (1.0f - Hazel::Engine::GetDeltaTime() * 2.0f);
	}

	camera.m_Zoom += camera.m_ZoomVel * Hazel::Engine::GetDeltaTime();
	camera.m_ZoomVel *= (1.0f - Hazel::Engine::GetDeltaTime() * 5.0f);

	if (camera.m_Zoom <= 0.00001f)
		camera.m_Zoom = 0.00001f;

}