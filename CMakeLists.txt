cmake_minimum_required(VERSION 3.16)
project(CMakeSFMLProject LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

include(FetchContent)

# Fetch discord-rpc
FetchContent_Declare(
    discord-rpc
    GIT_REPOSITORY https://github.com/discord/discord-rpc.git
    GIT_TAG v3.4.0
)
FetchContent_MakeAvailable(discord-rpc)

# Fetch SFML
FetchContent_Declare(
    SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x
)
FetchContent_MakeAvailable(SFML)

# Fetch ImGui
FetchContent_Declare(
    ImGui
    GIT_REPOSITORY https://github.com/ocornut/imgui
    GIT_TAG v1.89.9
)
FetchContent_MakeAvailable(ImGui)
FetchContent_GetProperties(ImGui SOURCE_DIR IMGUI_DIR)

set(IMGUI_SFML_FIND_SFML OFF)

# Fetch ImGui-SFML
FetchContent_Declare(
    ImGui-SFML
    GIT_REPOSITORY https://github.com/SFML/imgui-sfml
    GIT_TAG 2.6.x
)
FetchContent_MakeAvailable(ImGui-SFML)

include_directories(D:/Programming/CPPLibraries)

# Collect source files
set(SRC_DIR src)
file(GLOB SOURCES "${SRC_DIR}/*.cpp" "${SRC_DIR}/Classes/*.cpp" "${SRC_DIR}/Managers/*.cpp")

add_executable(MineGame ${SOURCES})

target_include_directories(MineGame PRIVATE
    ${discordrpc_SOURCE_DIR}/include
    ${SFML_SOURCE_DIR}/include
    ${IMGUI_DIR}
    D:/Programming/CPPLibraries
)

target_link_libraries(MineGame PRIVATE 
    sfml-graphics 
    ImGui-SFML::ImGui-SFML 
    discord-rpc
)

target_compile_features(MineGame PRIVATE cxx_std_17)

if(WIN32)
    add_custom_command(
        TARGET MineGame
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:MineGame>
        VERBATIM
    )
endif()
