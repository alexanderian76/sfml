cmake_minimum_required(VERSION 3.10)

# Имя вашего проекта
project(MyProject)

# Добавление стандартов C++17 (можно изменить на CXX20 или CXX23)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


# Указание всех исходных файлов
set(SOURCES
    main.cpp
    GlobalObjects.cpp
    ObjectController.cpp
    PlayerController.cpp
    Camera.cpp
    ./utils/utils.cpp
    ./Enemy/Enemy.cpp
    ./Enemy/EnemySpawner.cpp
)

find_package(SFML COMPONENTS Graphics Window System Audio Network REQUIRED)

# Создание исполняемого файла
add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME}
    sfml-graphics
    sfml-window
    sfml-system
    sfml-audio
    sfml-network
)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/assets/ 
     DESTINATION ${CMAKE_BINARY_DIR}/assets)