include (../defaults.pri)

TARGET = backend
TEMPLATE = lib

QT += network

SOURCES += \
    FileDownloader.cpp \
    Reddit.cpp \
    RedditPost.cpp \
    RedditSub.cpp
HEADERS += \
    FileDownloader.hpp \
    Reddit.hpp \
    RedditPost.hpp \
    RedditSub.hpp
