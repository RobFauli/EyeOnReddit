include(../defaults.pri)
TEMPLATE = app

CONFIG += console
CONFIG += app_bundle
QT += network

SOURCES += \
    main.cpp \
    Subreddit_tests.cpp \
    Submonitor_tests.cpp \
    Reddit_tests.cpp

LIBS += -L../src -lbackend
