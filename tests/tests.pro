include(../defaults.pri)
TEMPLATE = app

CONFIG += console
CONFIG += app_bundle
QT += network

SOURCES += \
    main.cpp \
    Reddit_tests.cpp \
    RedditSub_tests.cpp

LIBS += -L../src -lbackend
