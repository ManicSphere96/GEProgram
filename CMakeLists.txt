cmake_minimum_required(VERSION 3.0)
#set(CMAKE_GENERATOR_PLATFORM Win32)

project(MYENGINE)


find_package(OpenGL REQUIRED)
include_directories(sdk/Include src/renderer src/myengine)

link_directories(${CMAKE_SOURCE_DIR}/sdk/Lib)


link_libraries(glew32 SDL2 OpenAL32 OpenGL32)
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SAFESEH:NO")


# Avoid the weird SDL2main hack
add_definitions(-DSDL_MAIN_HANDLED)


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
   src/renderer/bugl2.h
   src/renderer/stb_image.h
)
#set_target_properties(renderer PROPERTIES COMPILE_FLAGS "-m32" LINK_FLAGS "-m32")
target_link_libraries(renderer)

add_library(myengine
 	src/myengine/Core.cpp
     src/myengine/Entity.cpp
     src/myengine/Component.cpp
     src/myengine/Keyboard.cpp
     src/myengine/Environment.cpp
     src/myengine/Screen.cpp
#     src/myengine/Sound.cpp
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
#     src/myengine/Sound.h
     src/myengine/Shader.h
     src/myengine/TriangleRenderer.h
     src/myengine/Transform.h
     src/myengine/Trigger.h
     src/myengine/Model.h
     src/myengine/Mouse.h
     src/myengine/MeshRenderer.h
 	src/myengine/Resource.h
#	src/myengine/stb_vorbis.c
)
#set_target_properties(myengine PROPERTIES COMPILE_FLAGS "-m32" LINK_FLAGS "-m32")
target_link_libraries(myengine)
link_libraries(renderer myengine glew32 OpenGL32)

add_executable(game
   src/game/main.cpp
   src/game/test.cpp
)
set_target_properties(game PROPERTIES LINK_FLAGS /stack:64000)

file (COPY sdk/Lib/glew32.dll DESTINATION ${CMAKE_BINARY_DIR}/Debug)
file (COPY sdk/Lib/OpenAL32.dll DESTINATION ${CMAKE_BINARY_DIR}/Debug)
file (COPY sdk/Lib/SDL2.dll DESTINATION ${CMAKE_BINARY_DIR}/Debug)
file (COPY Assets/Models/cube.obj DESTINATION ${CMAKE_BINARY_DIR}/Debug)
