#pragma once

#include <string>

#include "GL/glew.h"
#include <GLFW/glfw3.h>

#include "VertexArray.hpp"
#include "IndexBuffer.hpp"
#include "VertexBufferLayout.hpp"
#include "Shader.hpp"

class Renderer
{
	private:
		int m_WindowWidth;
		int m_WindowHeight;
		const char* m_WindowName;

		GLFWwindow* m_Window;

	public:
		Renderer();
		Renderer(int windowWidth, int windowHeight, const char* windowName);
		~Renderer();

		inline int GetWindowWidth() const { return m_WindowWidth; }
		inline int GetWindowHeight() const { return m_WindowHeight; }
		inline const char* GetWindowName() const { return m_WindowName; }

		void InitWindow();
		void Loop();
		void Draw(const VertexArray& vao, const IndexBuffer& ibo, const Shader& shader);
};

