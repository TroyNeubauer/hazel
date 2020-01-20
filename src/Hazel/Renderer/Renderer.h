#pragma once

#include <memory>

#include "VertexArray.h"
#include "Hazel/Camera/Camera.h"
#include "Shader.h"
#include "Hazel/Mesh/Mesh.h"
#include "Hazel/Enviorment/Light.h"

namespace Hazel {

	class Renderer
	{
	public:
		static void Init();
		static void BeginScene(Camera3D& camera, std::vector<Light>& lights);
		static void EndScene();

		static void Submit(const Mesh& mesh);

		static void Shutdown();


	private:
		struct SceneData
		{
			mat4 ViewProjectionMatrix;
			vec3 CameraPos;
		};

		static SceneData* s_SceneData;
	};


}