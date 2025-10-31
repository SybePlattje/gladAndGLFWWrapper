#include <glad/glad.h>
#include "GLContext.hpp"
#include "GLWindow.hpp"
#include "GLTexture.hpp"
#include "GLShaderFile.hpp"
#include "GLShaderProgram.hpp"
#include "GLUtils.hpp"
#include "GLMesh.hpp"
#include "GLBuffer.hpp"
#include <stdexcept>
#include <iostream>

int main()
{
    try 
    {
        GLContext context(4, 1);
        GLWindow window(800, 800, "test");

        if (!GLContext::sInitGlad())
        {
            std::cerr << "Glad init failed" << std::endl;
            return 1;
        }

        GLTexture tex;
        tex.setup("unicorns.jpeg");
        tex.bind();
        tex.unbind();
        std::cout << "texture id [" << tex.getTextureId() << "]" << std::endl;

        GLShaderFile vertexShader;
        if (!vertexShader.setup("basic.vert", GL_VERTEX_SHADER))
            return 1;

        GLShaderFile fragmentShader;
        if (!fragmentShader.setup("basic.frag", GL_FRAGMENT_SHADER))
            return 1;

        GLShaderProgram shaderProgram;
        if (!shaderProgram.setup())
            return 1;

        std::vector<GLShaderFile> shaders;
        shaders.emplace_back(std::move(vertexShader));
        shaders.emplace_back(std::move(fragmentShader));
        shaderProgram.attachShader(shaders);
        if (!shaderProgram.linkProgram())
            return 1;

        std::vector<float> vertices = {
            -1.f, -1.f, 0.f,
            1.f, -1.f, 0.f,
            1.f,  1.f, 0.f,
            -1.f,  1.f, 0.f
        };
        std::vector<unsigned int> indices = {
            0, 1, 2, 2, 3, 0
        };

        GLBuffer vertexBuffer(GLBuffer::e_Type::Array);
        vertexBuffer.setup();
        if (!vertexBuffer.setData<float>(vertices))
            return 1;

        GLBuffer indexBuffer(GLBuffer::e_Type::Element);
        indexBuffer.setup();
        if (!indexBuffer.setData<unsigned int>(indices))
            return 1;

        GLMesh mesh;
        if (!mesh.setup())
            return 1;

        std::vector<s_VertexAttribute> attributes = {{0, 3, GL_FLOAT, GL_FALSE, 4, 3}};
        if (!mesh.attachVertexBuffer(vertexBuffer, attributes))
            return 1;

        mesh.attachElementBuffer(indexBuffer);

        float brightness = 1.f;
        
        s_mat4 transform = {
           {
            {1.f, 0.f, 0.f, 0.f},
            {0.f, 1.f, 0.f, 0.f},
            {0.f, 0.f, 1.f, 0.f},
            {0.f, 0.f, 0.f, 1.f}
           } 
        };

        double start = GLContext::sGetTime();
        while (!window.shoulClose())
        {
            GLContext::sPollEvents();
            window.setClearColor(0.25f, 0.9f, 0.1f, 0.f);
            window.clear();
            double elapsed = GLContext::sGetTime() - start;
            if (5.0 < elapsed)
                window.setWindowClose();
            if (2.0 < elapsed && 3.0 > elapsed)
            {
                window.setSize(500, 500);
                window.setTitle("changed");
            }

            shaderProgram.bind();
            if (!shaderProgram.setUniform<float>("uBrightness", brightness))
                window.setWindowClose();
            if (!shaderProgram.setUniform<s_mat4>("uTransform", transform))
                window.setWindowClose();

            mesh.draw(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT);
            window.swapBuffers();
        }
        GLContext::sTerminate();
    }
    catch(std::runtime_error& e)
    {
        std::cerr << "[Runtime Error] " << e.what() << std::endl;
        return 1;
    }
    catch (std::exception& e)
    {
        std::cerr << "[Other error]" << e.what() << std::endl;
        return 1;
    }
}