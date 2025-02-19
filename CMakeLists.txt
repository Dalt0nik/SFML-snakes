cmake_minimum_required(VERSION 3.16)
project(Snakes LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

include_directories(Include)

add_executable(Snakes
    src/main.cpp
    src/Game.cpp
    src/Enemy.cpp
    src/Player.cpp
    src/Character.cpp
    src/EnemyBehavior.cpp)
target_link_libraries(Snakes PRIVATE sfml-graphics)
target_compile_features(Snakes PRIVATE cxx_std_17)


add_custom_command(TARGET Snakes POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy
                   ${CMAKE_SOURCE_DIR}/fonts/Valorax-lg25V.otf
                   $<TARGET_FILE_DIR:Snakes>)

if(WIN32)
    add_custom_command(
        TARGET Snakes
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:Snakes>
        VERBATIM)
endif()

install(TARGETS Snakes)
