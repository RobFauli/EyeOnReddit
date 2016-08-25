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

LIBS += \
    -L../src -lbackend


DISTFILES += \
    QML/android_main.qml \
    Assets/Icons/256x256/reddit_logo.png \
    Assets/Icons/96x96/reddit_icon_circle.png

HEADERS += \
    Desktop/src/Settings.hpp

SOURCES += \
    Desktop/src/Settings.cpp
