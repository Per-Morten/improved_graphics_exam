#version 410 core

// Input vertex data, different for all executions of this shader.
layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec3 vertexNormal_modelspace;
layout(location = 2) in vec2 textureCoordinate;
layout(location = 3) in uint textureIndex;

out vec2 fragmentTextureCoordinate;
out vec4 fragmentColor;
out vec3 fragmentPosition_cameraspace;
out vec3 fragmentNormal_cameraspace;
out vec3 lightDirection_cameraspace;

uniform vec4 VertexColor;
uniform mat4 ViewMatrix;
uniform mat4 ModelMatrix;
uniform mat3 NormalMatrix;
uniform vec3 LightDirection_worldspace;
uniform mat4 WorldScale;
uniform mat4 ProjectionMatrix;
uniform uint NumberOfRows;
uniform vec2 TextureOffset;

void main()
{
    vec4 vertexPosition = vec4(vertexPosition_modelspace,1.0);

    mat4 MVPS = ProjectionMatrix * ViewMatrix * WorldScale * ModelMatrix;

    gl_Position = MVPS * vertexPosition;

    fragmentColor = VertexColor;
//
    fragmentPosition_cameraspace = vec3(ViewMatrix * ModelMatrix * vec4(vertexPosition_modelspace, 1.0));
//
    fragmentNormal_cameraspace = normalize(NormalMatrix * vertexNormal_modelspace);

    lightDirection_cameraspace = normalize(vec3(ViewMatrix * vec4(LightDirection_worldspace, 0.0)));

    // Move the texture Coordinates into the numberOfRows areas aswell
    // So if the numberOfRows is 4, then the textureCoordinates that used to be in 0-1,
    // now turns into 0-0.25, and then we add on the textureOffset.
    //fragmentTextureCoordinate = (textureCoordinate/NumberOfRows) + TextureOffset;

    float col = textureIndex % 4;
    float row = textureIndex / 4;
    vec2 offset = vec2(col, row);
    fragmentTextureCoordinate = (textureCoordinate / 4.0f) + (offset / 4.0f);
}
