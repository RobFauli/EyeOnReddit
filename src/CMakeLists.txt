set(QT_MIN_VERSION "5.7.0")

set(CMAKE_AUTOMOC ON)

find_package(Qt5 ${QT_MIN_VERSION} CONFIG REQUIRED COMPONENTS
        Core
        Network
        )

set(LIBRARY_FILES
        backend/Subreddit.cpp backend/Subreddit.hpp
        backend/FileDownloader.cpp backend/FileDownloader.hpp main.cpp)

add_library(backend ${LIBRARY_FILES})

target_link_libraries(backend
        Qt5::Core
        Qt5::Network
        )
