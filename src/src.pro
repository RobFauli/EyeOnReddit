include (../defaults.pri)

TARGET = backend
TEMPLATE = lib

QT += network

SOURCES += \
    FileDownloader.cpp \
    Subreddit.cpp \
    Submonitor.cpp \
    Reddit.cpp
HEADERS += \
    FileDownloader.hpp \
    Subreddit.hpp \
    Submonitor.hpp \
    Reddit.hpp
