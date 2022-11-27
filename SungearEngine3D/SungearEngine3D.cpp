// SungearEngine3D.cpp: определяет точку входа для приложения.
//

#include <glad.h>
#include <GLFW/glfw3.h>
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
    float x, y, z;
    float r, g, b;
} vertices[8] =
{
    {  -1, +1, -1, 1.f, 0.f, 0.0f },
    {  +1, +1, -1, 1.f, 1.f, 0.0f },
    {  +1, -1, -1, 1.f, 0.f, 1.0f },
    {  -1, -1, -1, 0.f, 1.f, 0.0f },
    {  -1, +1, +1, 0.f, 0.f, 1.0f },
    {  +1, +1, +1, 1.f, 1.f, 1.0f },
    {  +1, -1, +1, 0.2f, 0.f, 0.7f },
    {  -1, -1, +1, 0.7f, 0.5f, 0.2f }
};

static const GLushort indices[] = {
    0, 1, 2,
    0, 2, 3,
    2, 1, 5,
    2, 5, 6,
    3, 2, 6,
    3, 6, 7,
    0, 3, 7,
    0, 7, 4,
    1, 0, 4,
    1, 4, 5,
    6, 5, 4,
    6, 4, 7,
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
    GLBuffer* index_buffer = new GLC::GLBuffer(GL_ELEMENT_ARRAY_BUFFER);

    vertex_buffer->Bind();
    vertex_buffer->Data(sizeof(vertices), vertices);//Биндим буффер и записываем в него данные

    index_buffer->Bind();
    index_buffer->Data(sizeof(indices), indices);//Биндим буффер и записываем в него данные

    string shaderText = FileUtils::ReadAllFile("D:/Pixelfield/C++Learning/SungearEngine3D/Core3D/Resources/Shaders/default.glsl");
    GLShader* shader = (new GLShader(shaderText))->Use();

    GLVertexArray* VAO = new GLVertexArray();

    GLVertexArrayAttribute vPos = {"vPos", vertex_buffer, sizeof(float) * 3, 3, GL_FLOAT};
    GLVertexArrayAttribute vCol = {"vCol", vertex_buffer, sizeof(float) * 3, 3, GL_FLOAT};
    VAO->PutAttribs(vPos, vCol);
    VAO->BuildAttribs(*shader);

    cout << shaderText << endl;

    mat4 m = mat4(1.0f);
    mat4 v = mat4(1.0f);
    mat4 p = mat4(1.0f);
    mat4 mvp = mat4();

    //m = translate(m, vec3(0.0f, 0.0f, 0.0f));
    v = translate(v, vec3(0.0f, 0.0f, -10.0f));

    glEnable(GL_DEPTH_TEST);

    while (!glfwWindowShouldClose(window))
    {
        float ratio;
        int width, height;

        glfwGetFramebufferSize(window, &width, &height);
        ratio = width / (float)height;

        glViewport(0, 0, width, height);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        m = rotate(mat4(1.0f), (float) glfwGetTime(), vec3(1.0f, 1.0f, 0.0f));
        p = perspective(45.0f, ratio, 0.1f, 100.0f);
        mvp = p * v * m;

        shader->Use();
        shader->uMat4x4("MVP", mvp);
        glDrawElements(GL_TRIANGLES, sizeof(indices), GL_UNSIGNED_SHORT, nullptr);
        //glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);

    glfwTerminate();
    exit(EXIT_SUCCESS);
}