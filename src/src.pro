include (../defaults.pri)

TARGET = backend
TEMPLATE = lib

QT += network

SOURCES += \
    FileDownloader.cpp \
    Subreddit.cpp
HEADERS += \
    FileDownloader.hpp \
    Subreddit.hpp
