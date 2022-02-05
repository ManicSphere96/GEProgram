cmake_minimum_required(VERSION 3.0)
project(MYENGINE)

include_directories(
	src # For myengine.h
	sdk # For glm.hpp
)

if(MSVC)
	include_directories(
		sdk/Include/SDL # For SDL.h
		sdk/Include # For glew.h
		sdk/Include # For glew.h
	)

	link_directories(
		${CMAKE_SOURCE_DIR}/sdk/Lib
		${CMAKE_SOURCE_DIR}/sdk/Lib
		${CMAKE_SOURCE_DIR}/sdk/Lib
	)

	set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SAFESEH:NO")
else()
	# Linux, Emscripten, macOS equivalents
endif()

# Avoid the weird SDL2main hack
if (MSVC)
	add_definitions(-DSDL_MAIN_HANDLED)
endif()

add_library(renderer
   src/renderer/renderer.cpp
   src/renderer/ShaderProgram.cpp
   src/renderer/VertexArray.cpp
   src/renderer/VertexBuffer.cpp
   src/renderer/Texture.cpp
   src/renderer/renderer.h
   src/renderer/ShaderProgram.h
   src/renderer/VertexArray.h
   src/renderer/VertexBuffer.h
   src/renderer/Texture.h
   src/renderer/Sampler.h
   src/renderer/bugl.h
   src/renderer/stb_image.h
)

target_link_libraries(renderer glew32 OpenGL32)

add_library(myengine
 	src/myengine/Core.cpp
     src/myengine/Entity.cpp
     src/myengine/Component.cpp
     src/myengine/Keyboard.cpp
     src/myengine/Environment.cpp
     src/myengine/Screen.cpp
     src/myengine/Sound.cpp
     src/myengine/TriangleRenderer.cpp
     src/myengine/Transform.cpp
     src/myengine/Model.cpp
     src/myengine/Mouse.cpp
     src/myengine/MeshRenderer.cpp
 	src/myengine/Resource.cpp
     src/myengine/Core.h
     src/myengine/Entity.h
     src/myengine/Component.h
     src/myengine/Keyboard.h
     src/myengine/Environment.h
     src/myengine/Screen.h
     src/myengine/Sound.h
     src/myengine/TriangleRenderer.h
     src/myengine/Transform.h
     src/myengine/Trigger.h
     src/myengine/Model.h
     src/myengine/Mouse.h
     src/myengine/MeshRenderer.h
 	src/myengine/Resource.h
	src/myengine/stb_vorbis.c
)

target_link_libraries(myengine renderer SDL2 openal32)

add_executable(game
   src/game/main.cpp
   src/game/test.cpp
)

target_link_libraries(game myengine)