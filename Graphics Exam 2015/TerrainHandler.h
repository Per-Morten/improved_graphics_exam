#pragma once
#include <vector>

#include "SceneObject.h"
#include "Renderer.h"


class TerrainHandler
{
public:
    using SceneObjectList = std::vector<SceneObject*>;
    using SceneObject3DList = std::vector<std::vector<std::vector<gsl::owner<SceneObject*>>>>;
    using HeightMap = std::vector<std::vector<int>>;

    TerrainHandler(Renderer& renderer,const HeightMap& heightMap) noexcept;
    ~TerrainHandler() noexcept;

    void update(float deltaTime) noexcept;
    void addCube(std::size_t xIndex, std::size_t zIndex) noexcept;
    void deleteCube(std::size_t xIndex, std::size_t zIndex) noexcept;

private:
    void createTerrain(const HeightMap& heightMap) noexcept;
    void hideUndrawableTerrain() noexcept;
    void createDrawableSceneList() noexcept;

    Renderer& _renderer;
    SceneObject3DList _sceneObjects{};
    SceneObjectList _drawableSceneObjects{};
};