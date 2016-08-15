include(../defaults.pri)

TEMPLATE = app
QT += quick

android {
    RESOURCES = \
        QML/Android/android.qrc
}

unix:!android|win32|win64 {
    RESOURCES = \
        QML/Desktop/desktop.qrc
}

LIBS += \
    -L../src -lbackend

SOURCES += main.cpp

DISTFILES += \
    QML/android_main.qml
