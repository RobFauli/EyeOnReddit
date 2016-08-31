include(../defaults.pri)

TEMPLATE = app
QT += quick

android {
    RESOURCES = \
        Android/QML/android.qrc
    SOURCES += Android/src/main.cpp
}

unix:!android|win32|win64 {
    QT += widgets gui
    RESOURCES = \
        Desktop/QML/desktop.qrc
    SOURCES += Desktop/src/main.cpp

    HEADERS += \
        Desktop/src/SystemTrayIcon.hpp

    SOURCES += \
        Desktop/src/SystemTrayIcon.cpp
}

RESOURCES += Assets/assets.qrc

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

HEADERS += \
    Desktop/src/Settings.hpp

SOURCES += \
    Desktop/src/Settings.cpp
TARGET = EyeOnReddit
unix:!android {
    target.path = /opt/EyeOnReddit/bin
    INSTALLS += target
}


