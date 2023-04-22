# Omicron Game-Development Kit (Omicron-Engine)
## Sub-part of the omicron game engine.

Usage in the main project. Include headers and then use this to write a renderer<br>

Current support opengl2/3 and d3d11 (vulkan and metal is in progress)
if you want to write a renderer, you can inheritage the base class "renderer_context_i" and custom it yourself.<br>

opengl context doesn't have to inheritage but d3d11 requieres. So just include "odk/windowapi/d3d11context.h" and inheritage that class and then custom it yourself.<br>

## vendor
**glad** : The opengl extension loader <br>
check src/glad to see license and source file.
check include/glad to see headers
