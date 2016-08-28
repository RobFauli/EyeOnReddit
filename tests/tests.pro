include(../defaults.pri)
TEMPLATE = app

CONFIG += console
CONFIG += app_bundle
QT += network qml

SOURCES += \
    main.cpp \
    Reddit_tests.cpp \
    Subreddit_tests.cpp


# Backend library (source folder):
win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../src/release/ -lbackend
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../src/debug/ -lbackend
else:unix: LIBS += -L$$OUT_PWD/../src/ -lbackend

INCLUDEPATH += $$PWD/../src
DEPENDPATH += $$PWD/../src

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../src/release/libbackend.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../src/debug/libbackend.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../src/release/backend.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../src/debug/backend.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../src/libbackend.a
