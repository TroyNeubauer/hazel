#pragma once

#include "Hazel/Camera/Camera.h"

#include "Hazel/Renderer/Texture.h"
#include "Hazel/Renderer2D/Animation2D.h"

namespace Hazel {

	class Renderer2D
	{
	public:
		static void Init();
		static void Shutdown();

		static void BeginScene(const Camera2D& cam);
		static void EndScene();

		// Primitives

		inline static void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const Animation2D& animation, float degrees) 
		{
			const Frame& frame = animation.GetFrame();
			glm::vec2 textureSize = { animation.GetTexture()->GetWidth(), animation.GetTexture()->GetHeight() };

			glm::vec2 top = glm::vec2(frame.Top.x, frame.Top.y) / textureSize;
			glm::vec2 bottom = glm::vec2(frame.Bottom.x, frame.Bottom.y) / textureSize;
			DrawQuad({ position.x, position.y, 0.0f }, size, top, bottom, animation.GetTexture(), { 1.0f, 1.0f, 1.0f, 1.0f }, degrees);
		}


		inline static void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture, float degrees) { DrawQuad({ position.x, position.y, 0.0f }, size, texture, degrees); }
		inline static void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture, float degrees) { DrawQuad(position, size, { 0.0f, 0.0f }, { 1.0f, 1.0f }, texture, { 1.0f, 1.0f, 1.0f, 1.0f }, degrees); }
		inline static void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec2& textureTop, const glm::vec2& textureBottom, const Ref<Texture2D>& texture, const glm::vec4& color, float degrees) { DrawQuad({ position.x, position.y, 0.0f }, size, textureTop, textureBottom, texture, color, degrees); }
		
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec2& textureTop, const glm::vec2& textureBottom, const Ref<Texture2D>& texture, const glm::vec4& color = { 1.0f, 1.0f , 1.0f , 1.0f }, float degrees = 0.0f);
	};

}
