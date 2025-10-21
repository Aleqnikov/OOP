cmake_minimum_required(VERSION 3.30)
project(Game)

set(CMAKE_CXX_STANDARD 20)

# Список всех исходных файлов
set(SOURCE_FILES
        main.cpp
        entites/Player.cpp
        entites/Enemy.cpp
        entites/EnemyBuilding.cpp
        entites/Entity.cpp
        entites/Weapon.cpp
        logic/managers/EnemyBuildingManager.cpp
        logic/managers/EnemyManager.cpp
        logic/managers/PlayerManager.cpp
        logic/World.cpp
        map/Field.cpp
        map/cells/Cell.cpp
        map/cells/ImpassableCell.cpp
        map/cells/SlowingCell.cpp
)

# Создание исполняемого файла (пробел после Game!)
add_executable(Game ${SOURCE_FILES})

# Указание директорий с заголовочными файлами
target_include_directories(Game PRIVATE
        ${CMAKE_SOURCE_DIR}/entites
        ${CMAKE_SOURCE_DIR}/logic
        ${CMAKE_SOURCE_DIR}/logic/managers
        ${CMAKE_SOURCE_DIR}/map
        ${CMAKE_SOURCE_DIR}/map/cells
)