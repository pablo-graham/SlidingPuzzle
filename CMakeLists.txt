cmake_minimum_required(VERSION 3.14)
project(MalenaTest)

include(FetchContent)
FetchContent_Declare(
        malena
        GIT_REPOSITORY https://github.com/daversmith/Malena.git
        GIT_TAG v0.2.5
)
FetchContent_MakeAvailable(malena)

add_executable(${PROJECT_NAME}
        main.cpp
        Game/Game.h
        Game/Game.cpp
        A_Star/A_Star.cpp
        A_Star/A_Star.h
        State/State.h
)

target_link_libraries(${PROJECT_NAME} PRIVATE Malena::Malena)