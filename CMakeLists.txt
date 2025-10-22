cmake_minimum_required(VERSION 3.30)
project(Game)

set(CMAKE_CXX_STANDARD 20)

# Список всех исходных файлов
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
        logic/managers/AllyManager.cpp
        logic/managers/EnemyBuildingManager.cpp
        logic/managers/EnemyManager.cpp
        logic/managers/EnemyTowerManager.cpp
        logic/managers/PlayerManager.cpp
        logic/World.cpp
        map/Field.cpp
        map/cells/Cell.cpp
        map/cells/ImpassableCell.cpp
        map/cells/SlowingCell.cpp
        map/cells/Events/TrapEvent.cpp

)

# Создание исполняемого файла
add_executable(Game ${SOURCE_FILES})

# Указание директорий с заголовочными файлами
target_include_directories(Game PRIVATE
        ${CMAKE_SOURCE_DIR}/entites
        ${CMAKE_SOURCE_DIR}/entites/Spells
        ${CMAKE_SOURCE_DIR}/logic
        ${CMAKE_SOURCE_DIR}/logic/managers
        ${CMAKE_SOURCE_DIR}/map
        ${CMAKE_SOURCE_DIR}/map/cells
        ${CMAKE_SOURCE_DIR}/map/cells/Events
)