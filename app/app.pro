include(../defaults.pri)

TEMPLATE = app

RESOURCES = QML/resources.qrc

LIBS += \
    -L../src -lbackend

SOURCES += main.cpp
