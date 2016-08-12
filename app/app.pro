include(../defaults.pri)

TEMPLATE = app

QT += quick
RESOURCES = QML/resources.qrc

LIBS += \
    -L../src -lbackend

SOURCES += main.cpp
