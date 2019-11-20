#include "Sandbox.h"

#include "Hazel/EntryPoint.h"
#include "Hazel/Enviorment/Material.h"

#include <iostream>
#include <random>
#include <filesystem>

#include "ExampleLayer.h"

Sandbox* sandbox;

Sandbox::Sandbox()
{

	m_Lights.push_back({ vec3(15000.0f, 100000.0f, -1000.0f), vec3(0.1f, 0.3f, 0.9f) });
	sandbox = this;
	PushLayer(new ExampleLayer());
	PushOverlay(new Hazel::DebugLayer());
	HZ_INFO("Created app");

	Hazel::BufferLayout layout = {
		{ Hazel::ShaderDataType::Float3, "a_Position" },
		{ Hazel::ShaderDataType::Float3, "a_Normal" },
		{ Hazel::ShaderDataType::Float2, "a_TextCoords" },
		{ Hazel::ShaderDataType::Float, "a_Brown" },
	};


	//Hazel::Ref<Hazel::Shader> shader = Hazel::Shader::Create("assets/shaders/test.glsl");

	m_Camera.reset(new Hazel::FPSCamera(50.0f));
	m_Camera->SetPosition(vec3(0.0f, 0.0f, 5.0f));
	m_Camera->RecalculateViewMatrix();

	//m_terrain = new Terrain(shader, -3000.0f, 3000.0f, -3000.0f, 3000.0f, -2.0f, 8, 100.0f);
	
	Hazel::Ref<Hazel::Texture2D> albedo = Hazel::Texture2D::Load("assets/material/rusted_iron/albedo.png");

	
	m_PBRShader = Hazel::Shader::Create("assets/shaders/pbr.glsl");
	for (int x = 0; x <= 5; x++)
	{
		for (int y = 0; y < 5; y++)
		{
			Hazel::Ref<Hazel::Material> material = Hazel::R(new Hazel::Material(albedo, 0.0f, 0.0f, 0.0f));
			material->Metallic = x / 5.0f;
			material->Roughness = y / 5.0f;
			Hazel::Ref<Hazel::IcoashedronMesh> mesh = Hazel::R(new Hazel::IcoashedronMesh(material, 1.0f));
			mesh->MeshShader = m_PBRShader;
			mesh->Subdivide(2);
			m_Meshes.push_back(mesh);
			mesh->Position = { 2.5f * x, 2.5f * y, 0.0f };

		}
	}
}

std::ostream& operator<<(std::ostream& os, const vec3& vec) { return os << '[' << vec.x << ", " << vec.y << ", " << vec.z << ", " << ']'; }

void Sandbox::Update()
{
	if(!Paused) m_Camera->Update();
	GetWindow().ShowCursor(Paused);
}

void Sandbox::Render()
{

	Hazel::RenderCommand::SetClearColor(glm::vec4(1.0f, 0.0f, 1.0f, 1.0f));
	Hazel::RenderCommand::Clear();

	Hazel::Renderer::BeginScene(*m_Camera, m_Lights);

	//Hazel::Renderer::Submit(*m_terrain);

	if (Hazel::Input::IsMouseButtonPressed(HZ_MOUSE_BUTTON_5) || Hazel::Input::IsKeyPressed(HZ_KEY_H))
	{
		glPolygonMode(GL_FRONT, GL_LINE);
		glPolygonMode(GL_BACK, GL_LINE);
	}

	m_PBRShader->Bind();
	m_PBRShader->SetFloat3("u_LightPosition", m_Lights[0].position);
	m_PBRShader->SetFloat3("u_LightColor", m_Lights[0].color);
	for (auto& mesh : m_Meshes) {
		mesh->MeshShader->SetFloat3("u_CamPos", m_Camera->GetPosition());
		mesh->MeshShader->SetFloat("u_Metallic", mesh->MeshMaterial->Metallic);
		mesh->MeshShader->SetFloat("u_Roughness", mesh->MeshMaterial->Roughness);
		mesh->MeshShader->SetFloat("u_AO", mesh->MeshMaterial->AO);
		HZ_CORE_WARN("Rough {}", mesh->MeshMaterial->Roughness);

		Hazel::Renderer::Submit(*mesh);
	}
	glPolygonMode(GL_FRONT, GL_FILL);
	glPolygonMode(GL_BACK, GL_FILL);
	
	Hazel::Renderer::EndScene();
	//Hazel::Renderer::Flush();

}

Sandbox::~Sandbox()
{

}


Hazel::Application* Hazel::CreateApplication(int argc, char** argv)
{
	return new Sandbox();
}
