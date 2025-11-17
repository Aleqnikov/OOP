cmake_minimum_required(VERSION 3.16)
project(Game)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Подтягиваем nlohmann::json
include(FetchContent)
FetchContent_Declare(
        nlohmann_json
        GIT_REPOSITORY https://github.com/nlohmann/json.git
        GIT_TAG v3.11.2
)
FetchContent_MakeAvailable(nlohmann_json)

# Список всех исходников
set(SOURCE_FILES
        main.cpp
        entites/Ally.cpp
        entites/Enemy.cpp
        entites/EnemyBuilding.cpp
        entites/EnemyTower.cpp
        entites/Entity.cpp
        entites/Hand.cpp
        entites/Player.cpp
        entites/Weapon.cpp
        entites/Spells/DirDamageSpell.cpp
        entites/Spells/TrapSpell.cpp
        entites/Spells/AreaDmgSpell.cpp
        entites/Spells/EnhacementSpell.cpp
        entites/Spells/SummSpell.cpp
        logic/managers/EnemyBuildingManager.cpp
        logic/managers/EnemyTowerManager.cpp
        logic/managers/PlayerManager.cpp
        logic/World.cpp
        Gameloop/GameLoop.cpp
        Gameloop/Visualizer.cpp

        map/Field.cpp
        map/cells/Cell.cpp
        map/cells/ImpassableCell.cpp
        map/cells/SlowingCell.cpp
        map/cells/Events/TrapEvent.cpp
        logic/GameSaver.cpp
)

# Создаём исполняемый файл
add_executable(Game ${SOURCE_FILES})

# Указываем include директории
target_include_directories(Game PRIVATE
        ${CMAKE_SOURCE_DIR}/entites
        ${CMAKE_SOURCE_DIR}/entites/Spells
        ${CMAKE_SOURCE_DIR}/logic
        ${CMAKE_SOURCE_DIR}/Exceptions
        ${CMAKE_SOURCE_DIR}/logic/managers
        ${CMAKE_SOURCE_DIR}/map
        ${CMAKE_SOURCE_DIR}/Gameloop
        ${CMAKE_SOURCE_DIR}/map/cells
        ${CMAKE_SOURCE_DIR}/map/cells/Events
)

# Линкуем библиотеку json
target_link_libraries(Game PRIVATE nlohmann_json::nlohmann_json)
