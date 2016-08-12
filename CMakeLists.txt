cmake_minimum_required(VERSION 3.2.2)
project(PhysicsSandbox)

set(QT_MIN_VERSION "5.7.0")

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -ansi -pedantic")
set(CMAKE_CXX_STANDARD 14)

include_directories(src/backend)




# Builds the backend library
add_subdirectory(src)

# Test code and google test library
add_subdirectory(unittests)

find_package(Qt5 ${QT_MIN_VERSION} CONFIG REQUIRED COMPONENTS
        Core
        Gui
        Qml
        Quick
        )

set(SOURCE_FILES src/main.cpp)
qt5_add_resources(RESOURCES src/QML/resources.qrc)
add_executable(main ${SOURCE_FILES} ${RESOURCES})
target_link_libraries(main
        backend
        Qt5::Core
        Qt5::Gui
        Qt5::Qml
        Qt5::Quick
        )
