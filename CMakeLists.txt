cmake_minimum_required(VERSION 3.10...3.50)

# You can use Vscode or Visual Studio. Make sure you know what your doing!

project(Apple_Falls)

include(FetchContent)

# Use thirdparty libs

# Raylib: https://github.com/raysan5/raylib
# Nlohmann Json: https://github.com/nlohmann/json 

FetchContent_Declare(
    raylib
    URL https://github.com/raysan5/raylib/archive/refs/tags/6.0.zip
)

FetchContent_Declare(
    json
    URL https://github.com/nlohmann/json/archive/refs/tags/v3.12.0.zip
)

set(BUILD_EXAMPLES OFF CACHE INTERNAL "")

FetchContent_MakeAvailable(raylib json)

# Add the files here, as you go

set(
SOURCE_FILES

    src/main.cpp
)

add_executable(Apple_Falls ${SOURCE_FILES})
target_link_libraries(Apple_Falls raylib nlohmann_json::nlohmann_json)

if(WIN32)

    target_sources(Apple_Falls PRIVATE windows/app.rc)
    target_link_options(Apple_Falls PRIVATE $<$<CONFIG:Release>:-mwindows>)
elseif(APPLE)

    target_link_options(Apple_Falls PRIVATE $<$<CONFIG:Release>:-MACOSX_BUNDLE>)
endif()

target_compile_definitions(Apple_Falls PUBLIC $<$<CONFIG:Debug>:DEBUG_ENABLED>)

if("${PLATFORM}" STREQUAL "Web")

    message(SEND_ERROR "Do not build in this project in the Web as it doesn't work!")
endif()

if(APPLE)

    target_link_libraries(${PROJECT_NAME} "-framework IOKit")
    target_link_libraries(${PROJECT_NAME} "-framework Cocoa")
    target_link_libraries(${PROJECT_NAME} "-framework OpenGL")
endif()

message("Operation Complete! Configured Correctly!")