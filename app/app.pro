include(../defaults.pri)

TEMPLATE = app
QT += quick

android {
    RESOURCES = \
        Android/QML/android.qrc
    SOURCES += Android/src/main.cpp
}

unix:!android|win32|win64 {
    RESOURCES = \
        Desktop/QML/desktop.qrc
    SOURCES += Desktop/src/main.cpp
}

LIBS += \
    -L../src -lbackend


DISTFILES += \
    QML/android_main.qml
