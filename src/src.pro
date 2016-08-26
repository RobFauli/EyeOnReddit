include (../defaults.pri)

TARGET = backend
TEMPLATE = lib
CONFIG += staticlib
QT += network qml

SOURCES += \
    FileDownloader.cpp \
    Reddit.cpp \
    RedditPost.cpp \
    Subreddit.cpp
HEADERS += \
    FileDownloader.hpp \
    Reddit.hpp \
    RedditPost.hpp \
    Subreddit.hpp

#unix:!android {
#    target.path = /usr/local/EyeOnReddit/src
#    INSTALLS += target
#}
