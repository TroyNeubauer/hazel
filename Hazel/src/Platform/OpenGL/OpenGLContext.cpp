
#include "hzpch.h"
#include "OpenGLContext.h"
#include "Platform/OpenGL/OpenGLImGuiLayer.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>


namespace Hazel {

	void OpenGLContext::Init()
	{
		int status = gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
		glfwSwapInterval(1);
		HZ_CORE_ASSERT(status, "Failed to initialize Glad!");
		HZ_CORE_INFO("Created OpenGL Context, Version: {}", glGetString(GL_VERSION));
	}

	void OpenGLContext::SwapBuffers()
	{
		for(auto window : m_Handles)
			glfwSwapBuffers((GLFWwindow*) window->GetNativeWindow());
		glClearColor(0, 0, 0, 1);
		glClear(GL_COLOR_BUFFER_BIT);
	}
	void OpenGLContext::OnWindowResize(Window* window, int width, int height)
	{
		glViewport(0, 0, width, height);
	}

	void OpenGLContext::Destroy()
	{
	}

	void OpenGLContext::AddWindow(Window* window)
	{
		m_Handles.push_back(window);
		glfwMakeContextCurrent((GLFWwindow*) window->GetNativeWindow());
	}

	void OpenGLContext::RemoveWindow(Window * window)
	{
		auto it = std::find(m_Handles.begin(), m_Handles.end(), window);
		if (it != m_Handles.end())
			m_Handles.erase(it);
	}

	GraphicsAPIType OpenGLContext::GetAPIType() { return GraphicsAPI::OPEN_GL; }

	ImGuiLayer* OpenGLContext::CreateImGuiLayer()
	{
		return new OpenGLImGuiLayer();
	}
}
