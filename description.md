# Classes
## Camera
Standard camera, can move around, also responsible for calculating the view matrix.

## Input handler
Handed out by teacher. Mainly it just helps with repeating keys, and "converting" key presses to events
which is added to the central event queue.

## TerrainHandler
The TerrainHandler is responsible for all the visual objects in the world (which is everything except the skybox).
The responsibility includes:
* Creating the terrain based on a HeightMap
* Asking all visible objects to update and draw themselves
* Adding and removing objects from the world
* Ensuring that the terrain objects have the correct texture based on their height about the ground
* "Simulating" rain or snow

For example, cubes that are hidden by other cubes should not be visible.
All the regular ground cubes are heap allocated and the pointers are stored in a 3d std::vector.
Pointers to the ground cubes that are visible is stored in another vector, these are the only ones that are actually updated and drawn.

### SceneObject
All the visual objects that the TerrainHandler is responsible for are SceneObjects.
SceneObjects holds identifiers (usually std::string) to the resources that should be used when drawing them.
Additionally they contain transform related information, and are also responsible for calculating their own model matrix if needed.
The facingDirection variable is only relevant for the "skybox", as I hacked in support for that "feature" by just changing the glCullFace.

## Renderer
Point of entry for all graphics related stuff.
The renderer is responsible for all the communication with OpenGL and also holds all the graphics resources,
like meshes, textures and shader programs.
However, these resources are again wrapped in their own classes, which supplies relevant construction, binding and querying options.

### Mesh
Simply holds all information needed for a mesh. In the constructor it creates VBOS, VAOS, IBO's etc.
And when drawn it binds the vertexArray, buffer and draws all the elements.

### Texture
Loads the textures from file using stb_image, transfers it to graphics memory and keeps track of the handle.
It also remembers how many rows there are in the texture, to support basic texture atlas functionality.

### Shader Program
Loads and compiles fragment and vertex shaders. Also keeps track of all the uniforms existing within a shader program.
The handles/addresses for these can be queried from the outside.

# Basic Premise of Game Loop
TerrainHandler updates and draws all the sceneObjects that are visible, and any potential downpour.
Updating the regular sceneobjects doesn't actually amount to anything, as they are static, and their modelmatrix therefore stays the same.
However, each piece of downpour needs its modelmatrix re-calculated every frame.

When drawing each sceneobject sends the resources it needs down to the renderer.
For each draw call the renderer checks if anything actually needs to change,
or if we are just using the same configuration as the previous draw call.
Additionally it fetches the viewmatrix from the camera.
After this it orders the requested mesh to draw itself.

For the exam we were supposed to do scaling in the vertex shader, so the calculation of the MVP is done there.

## Extra features
On top of the basic premise are a bunch of "features" that are hacked in.
These include:

* A literal skybox (i.e. just a box with a texture where I tell OpenGL to cull the opposite faces, so it faces inwards).
* Changing the direction of the light, "simulating" the sun moving across the landscape.
* Changing the scale of the world
* Creating and destroying blocks below you
* Toggle warp mode
    * Just a switch that messes with the FOV, creating a traditional "warp drive" visual effect
* Toggling downpour
    * These are the ones that actually needs their modelmatrix recalculated each frame.
* Switching through texture sets
* Toggling "winter" mode
