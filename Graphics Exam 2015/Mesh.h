//===========================================================
// File: Mesh.h	
// StudentName: Per-Morten Straume                          
//                                                          
// Exam 2015: IMT-2531 Graphics Programming Exam.                                
//===========================================================
#pragma once
#include <vector>

#include <GL\glew.h>
#include <glm\glm.hpp>

class Mesh
{
public:
    using IndexBufferObject = GLuint;
    using VertexBufferObject = GLuint;
    using VertexAttributeObject = GLuint;

    Mesh() = delete;
    Mesh(const std::vector<glm::vec3>& vertexPositions,
         const std::vector<glm::vec3>& vertexNormals,
         const std::vector<glm::vec2>& textureCoordinates,
         const std::vector<GLuint>& IBO,
         const std::vector<GLuint>& textureIndices = {}) noexcept;
    ~Mesh() noexcept;

    void draw() noexcept;
private:
    VertexBufferObject _positionsVBO{};
    VertexBufferObject _normalsVBO{};
    VertexBufferObject _textureCoordinateVBO{};
    VertexBufferObject _textureIndicesVBO{};
    IndexBufferObject _indexBufferObject{};
    VertexAttributeObject _vertexAttributeObject{};
    GLuint _drawCount{};
};