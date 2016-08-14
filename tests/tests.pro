include(../defaults.pri)
TEMPLATE = app

CONFIG += console
CONFIG += app_bundle

SOURCES += \
    main.cpp \
    Subreddit_tests.cpp \
    Submonitor_tests.cpp \
    Reddit_tests.cpp

LIBS += -L../src -lbackend
