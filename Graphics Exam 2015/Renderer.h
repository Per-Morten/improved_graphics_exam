//===========================================================
// File: Renderer.h
// StudentName: Per-Morten Straume
//
// Exam 2015: IMT-2531 Graphics Programming Exam.
//===========================================================
#pragma once
#include <string>
#include <unordered_map>

#include <gl\glew.h>
#include <gl\glu.h>
#include <glm\glm.hpp>
#include <SDL.h>
#include <SDL_opengl.h>

#include "Camera.h"
#include "Mesh.h"
#include "ShaderProgram.h"
#include "Texture.h"
#include "DegToRad.h"

class Renderer
{
public:
    enum class FacingDirection
    {
        FRONT,
        BACK,
    };

    static constexpr auto groundTexture = "Ground";
    static constexpr auto skyboxDayTexture = "SkyBoxDay";
    static constexpr auto skyboxNightTexture = "SkyBoxNight";
    static constexpr auto cubeMesh = "Cube";
    static constexpr auto regularShader = "DirectionalFullTexture";
    static constexpr auto nonScalingShader = "nonScaling";
    static constexpr auto nonScalingWLight = "nonScalingWLight";
    static constexpr auto windowName = "Graphics Exam 2015 - Per-Morten Straume" ;
    static constexpr float warpFov = 179.0f;
    static constexpr float lightRotationSpeed = 10.0f;
    static constexpr float worldUpScaleRate = 1.1f;
    static constexpr float worldDownScaleRate = 0.9f;
    static constexpr float lowerNightAngle = 45.0f;
    static constexpr float upperNightAngle = 145.0f;
    const glm::vec4 clearColor = { 0.25f, 0.25f, 0.25f, 1.0f };
    const GLint width{};
    const GLint height{};
    const float fieldOfView = glm::pi<float>()/3.0f;

    Renderer(GLint width, GLint height, Camera& _camera) noexcept;
    ~Renderer() noexcept;

    void clear() noexcept;
    void render(const std::string& shaderName,
                const std::string& meshName,
                const std::string& textureName,
                const glm::mat4& modelMatrix,
                const glm::vec4& color,
                GLuint textureIndex,
                FacingDirection facing = FacingDirection::BACK) noexcept;
    void present() noexcept;

    bool initialize() noexcept;
    bool windowIsOpen() const noexcept;

    void advanceLight(float deltaTime) noexcept;
    void regressLight(float deltaTime) noexcept;

    void increaseWorldScale() noexcept;
    void decreaseWorldScale() noexcept;
    void resetWorldScale() noexcept;
    void toggleWarpMode() noexcept;


    void keepWindowOpen(bool isOpen) noexcept;

    bool isDayTime() const noexcept;

    void setWindowTitle(const char* title);

    void logFrameStats();

private:
    // Rendering Functions
    // object related
    void setColorUniform(const std::string& shaderName, bool newShader, const glm::vec4& color) noexcept;
    void setModelMatrixUniform(const std::string& shaderName, bool newShader, const glm::mat4& modelMatrix) noexcept;
    void setNormalMatrixUniform(const std::string& shaderName, bool newShader, const glm::mat4& modelMatrix) noexcept;
    void setTextureOffsetUniform(const std::string& shaderName, bool newShader, bool newTexture, GLuint textureIndex, GLuint numberOfRows) noexcept;
    void setNumberOfRows(const std::string& shaderName, bool newShader, bool newTexture, GLuint numberOfRows) noexcept;

    // Static for each total draw round
    void setViewMatrixUniform(const std::string& shaderName, bool newShader) noexcept;
    void setProjectionMatrixUniform(const std::string& shaderName, bool newShader) noexcept;
    void setAmbientFactorUniform(const std::string& shaderName, bool newShader) noexcept;
    void setLightDirectionUniform(const std::string& shaderName, bool newShader) noexcept;
    void setWorldScaleUniform(const std::string& shaderName, bool newShader) noexcept;

    // initializing Functions
    bool initializeSDL() noexcept;
    bool createWindow() noexcept;
    bool createContext() noexcept;
    bool initializeGlew() noexcept;
    bool setVsyncOn() noexcept;
    void initializeOpenGL() noexcept;
    void initializeVariables() noexcept;

    Camera& _camera;
    SDL_Window* _window{};
    SDL_GLContext _context{};
    float _ambientFactor{ 0.1f };
    glm::vec3 _lightDirection{cos(degToRad(120.0f)), sin(degToRad(120.0f)), 0.0f};

    glm::mat4 _worldScale{1 };
    glm::mat4 _projectionMatrix{};
    std::unordered_map<std::string, ShaderProgram*> _shaderPrograms{};
    std::unordered_map<std::string, Mesh*> _meshes{};
    std::unordered_map<std::string, Texture*> _textures{};

    bool _windowIsOpen{};
    bool _warpMode{false};

    float _sunAngle{ 120.0f };

    // Shader tracking vars.
    int _frameNumber{};
    int _shaderChanges{};
    int _textureChanges{};
    int _cullChanges{};

    int _setColorUniformChanges{};
    int _setModelMatrixUniformChanges{};
    int _setNormalMatrixUniformChanges{};
    int _setTextureOffsetUniformChanges{};
    int _setNumberOfRowsChanges{};

    int _setViewMatrixUniformChanges{};
    int _setProjectionMatrixUniformChanges{};
    int _setAmbientFactorUniformChanges{};
    int _setLightDirectionUniformChanges{};
    int _setWorldScaleUniformChanges{};
};

