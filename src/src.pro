include (../defaults.pri)

TARGET = backend
TEMPLATE = lib

QT += network

SOURCES += \
    FileDownloader.cpp \
    Subreddit.cpp \
    Reddit.cpp
HEADERS += \
    FileDownloader.hpp \
    Subreddit.hpp \
    Reddit.hpp
