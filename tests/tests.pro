include(../defaults.pri)
TEMPLATE = app

CONFIG += console
CONFIG += app_bundle
QT += network

SOURCES += \
    main.cpp \
    Reddit_tests.cpp \
    Subreddit_tests.cpp

LIBS += -L../src -lbackend
