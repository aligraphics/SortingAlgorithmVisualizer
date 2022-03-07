#include "Renderer.hpp"

#include <iostream>
#include <Windows.h>

#include "VertexArray.hpp"
#include "VertexBuffer.hpp"
#include "IndexBuffer.hpp"

#include "Sort.hpp"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

Renderer::Renderer(int windowWidth, int windowHeight, const char* windowName)
	: m_WindowWidth(windowWidth), m_WindowHeight(windowHeight), m_WindowName(windowName), m_Window(nullptr)
{

}

Renderer::~Renderer()
{
	glfwTerminate();
}

void Renderer::InitWindow()
{
	if (!glfwInit())
		return;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    m_Window = glfwCreateWindow(m_WindowWidth, m_WindowHeight, m_WindowName, NULL, NULL);
    if (!m_Window)
    {
        glfwTerminate();
        return;
    }
    glViewport(0, 0, m_WindowWidth, m_WindowHeight);
    glfwMakeContextCurrent(m_Window);

    glfwSwapInterval(1);

    if (glewInit() != GLEW_OK) {
        std::cout << "ERROR!" << std::endl;
    }

    std::cout << glGetString(GL_VERSION) << std::endl;
}

void Renderer::Loop()
{
    float positions[] =
    {
         0.0f,    0.0f,   // 0
         30.0f,   0.0f,   // 1

         30.0f, 100.0f,   // 2
         0.0f,  100.0f,   // 3
    };

    unsigned int indices[] =
    {
        0, 1, 2, // Bottom right
        2, 3, 0  // Top left
    };

    VertexArray vao;
    VertexBuffer vbo(positions, sizeof(positions));

    VertexBufferLayout layout;
    layout.Push<float>(2);
    vao.AddBuffer(vbo, layout);

    IndexBuffer ibo(indices, sizeof(indices) / sizeof(unsigned int));

    Shader shader("res/shaders/Shader.shader");
    shader.Bind();

    shader.SetUniform4f("u_BarColor", 1.0f, 0.0f, 0.0f, 1.0f);

    vao.Unbind();
    vbo.Unbind();
    ibo.Unbind();
    shader.Unbind();

    glm::mat4 proj = glm::ortho(0.0f, (float)m_WindowWidth, 0.0f, (float)m_WindowHeight);
    glm::mat4 view = glm::mat4(1.0f);

    int barWidth = 5;
    int amount = m_WindowWidth / barWidth;
    std::cout << "Sorting " << amount << " numbers\n";

    Sort sort;
    auto heights = sort.GenerateHeights(m_WindowHeight, amount);

    while (!glfwWindowShouldClose(m_Window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        for (int i = 0; i < amount; i++)
        {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, glm::vec3(i * barWidth, 0, 0));
            model = glm::scale(model, glm::vec3(1.0f, heights[i], 1.0f));

            glm::mat4 mvp = proj * view * model;
            shader.SetUniformMat4("u_MVP", mvp);

            Draw(vao, ibo, shader);
        }

        if (sort.IsSorted() == false) {
            sort.InsertionSort(heights);
        }
        else {
            shader.SetUniform4f("u_BarColor", 0.0f, 1.0f, 0.0f, 1.0f);
        }

        glfwSwapBuffers(m_Window);
        glfwPollEvents();

        Sleep(10);
    }
}

void Renderer::Draw(const VertexArray& vao, const IndexBuffer& ibo, const Shader& shader)
{
    shader.Bind();
    vao.Bind();

    glDrawElements(GL_TRIANGLES, ibo.GetCount(), GL_UNSIGNED_INT, nullptr);
}
