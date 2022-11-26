// SungearEngine3D.cpp: определяет точку входа для приложения.
//

#include "SungearEngine3D.h"
#include <glad.h>
#include <GLFW/glfw3.h>
#include "../GLFW/deps/linmath.h"
#include <Core3D/Core3DMain.h>
#include <Core3D/GLControl.h>
#include <Core3D/Utils.h>   


using namespace std;
using namespace Core3D;
using namespace GLC;
using namespace Utils;

void error_callback(int error, const char* description)
{
	fprintf(stderr, "Error: %s\n", description);
}


static const struct
{
    float x, y;
    float r, g, b;
} vertices[3] =
{
    { -0.6f, -0.4f, 1.f, 0.f, 0.f },
    {  0.6f, -0.4f, 0.f, 1.f, 0.f },
    {   0.f,  0.6f, 0.f, 0.f, 1.f }
};

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}

int main(void)
{
    GLFWwindow* window;

    glfwSetErrorCallback(error_callback);

    if (!glfwInit())
        exit(EXIT_FAILURE);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

    window = glfwCreateWindow(640, 480, "Simple example", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwSetKeyCallback(window, key_callback);

    glfwMakeContextCurrent(window);
    //gladLoadGL(glfwGetProcAddress);
    gladLoadGL();
    glfwSwapInterval(1);

    // NOTE: OpenGL error checks have been omitted for brevity

    GLBuffer* vertex_buffer = new GLC::GLBuffer();
    vertex_buffer->Bind()->Data(sizeof(vertices), vertices);//Биндим буффер и записываем в него данные

    string shaderText = FileUtils::ReadAllFile("D:/Pixelfield/C++Learning/SungearEngine3D/Core3D/Resources/Shaders/default.glsl");
    GLShader* shader = (new GLShader(shaderText))->Use();

    GLVertexArray* VAO = (new GLVertexArray(shader))->Bind();

    GLVertexArrayAttribute vPos = {"vPos", vertex_buffer, sizeof(float) * 2, 2, GL_FLOAT};
    GLVertexArrayAttribute vCol = {"vCol", vertex_buffer, sizeof(float) * 3, 3, GL_FLOAT};
    VAO->PutAttrib(vPos);
    VAO->PutAttrib(vCol);
    VAO->BuildAttribs();

    cout << shaderText << endl;

    while (!glfwWindowShouldClose(window))
    {
        float ratio;
        int width, height;
        mat4x4 m, p, mvp;

        glfwGetFramebufferSize(window, &width, &height);
        ratio = width / (float)height;

        glViewport(0, 0, width, height);
        glClear(GL_COLOR_BUFFER_BIT);

        mat4x4_identity(m);
        mat4x4_rotate_Z(m, m, (float)glfwGetTime());
        mat4x4_ortho(p, -ratio, ratio, -1.f, 1.f, 1.f, -1.f);
        mat4x4_mul(mvp, p, m);

        shader->Use();
        shader->uMat4x4("MVP", mvp);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);

    glfwTerminate();
    exit(EXIT_SUCCESS);
}