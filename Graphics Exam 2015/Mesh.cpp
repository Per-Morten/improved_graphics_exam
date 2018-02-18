//===========================================================
// File: Mesh.cpp	
// StudentName: Per-Morten Straume                          
//                                                          
// Exam 2015: IMT-2531 Graphics Programming Exam.                                
//===========================================================
#include "Mesh.h"
#include "GLTypes.h"

Mesh::Mesh(const std::vector<glm::vec3>& vertexPositions,
           const std::vector<glm::vec3>& vertexNormals,
           const std::vector<glm::vec2>& textureCoordinates,
           const std::vector<GLuint>& IBO,
           const std::vector<GLuint>& textureIndices) noexcept
    : _drawCount(IBO.size())
{
    glGenVertexArrays(1, &_vertexAttributeObject);
    glBindVertexArray(_vertexAttributeObject);

    glGenBuffers(1, &_positionsVBO);
    glBindBuffer(GL_ARRAY_BUFFER, _positionsVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexPositions.front()) * vertexPositions.size(), vertexPositions.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, GLTypes::vec3, GL_FLOAT, GL_FALSE, 0, nullptr);
    glEnableVertexAttribArray(0);

    if (!vertexNormals.empty())
    {
        glGenBuffers(1, &_normalsVBO);
        glBindBuffer(GL_ARRAY_BUFFER, _normalsVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertexNormals.front()) * vertexNormals.size(), vertexNormals.data(), GL_STATIC_DRAW);
        glVertexAttribPointer(1, GLTypes::vec3, GL_FLOAT, GL_FALSE, 0, nullptr);
        glEnableVertexAttribArray(1);
    }

    if (!textureCoordinates.empty())
    {
        glGenBuffers(1, &_textureCoordinateVBO);
        glBindBuffer(GL_ARRAY_BUFFER, _textureCoordinateVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(textureCoordinates.front()) * textureCoordinates.size(), textureCoordinates.data(), GL_STATIC_DRAW);
        glVertexAttribPointer(2, GLTypes::vec2, GL_FLOAT, GL_FALSE, 0, nullptr);
        glEnableVertexAttribArray(2);
    }

    if (!textureIndices.empty())
    {
        glGenBuffers(1, &_textureIndicesVBO);
        glBindBuffer(GL_ARRAY_BUFFER, _textureIndicesVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(textureIndices.front()) * textureIndices.size(), textureIndices.data(), GL_STATIC_DRAW);
        glVertexAttribIPointer(3, GLTypes::uint, GL_UNSIGNED_INT, 0, nullptr);
        glEnableVertexAttribArray(3);
    }

    glGenBuffers(1, &_indexBufferObject);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _indexBufferObject);
    if (!IBO.empty())
    {
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(IBO.front()) * IBO.size(), IBO.data(), GL_STATIC_DRAW);
    }
    else
    {
        std::vector<GLuint> newIBO;
        for (GLuint i = 0; i < vertexPositions.size(); ++i)
        {
            newIBO.emplace_back(i);
        }
        _drawCount = newIBO.size();
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(newIBO.front()) * newIBO.size(), newIBO.data(), GL_STATIC_DRAW);
    }
    
    //glBindVertexArray(_vertexAttributeObject);
}

Mesh::~Mesh() noexcept
{
    glDeleteVertexArrays(1, &_vertexAttributeObject);
    glDeleteBuffers(1, &_positionsVBO);
    glDeleteBuffers(1, &_normalsVBO);
    glDeleteBuffers(1, &_textureCoordinateVBO);
    glDeleteBuffers(1, &_indexBufferObject);
    glDeleteBuffers(1, &_textureIndicesVBO);
}

void Mesh::draw() noexcept
{
    glBindVertexArray(_vertexAttributeObject);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _indexBufferObject);
    glDrawElements(GL_TRIANGLES, _drawCount, GL_UNSIGNED_INT, nullptr);
}
