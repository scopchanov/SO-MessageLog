#------------------------------
#
# Project: MessageLog
# Author: Michael Scopchanov
# Created: 01-11-2018 18:41
# IDE: Qt Creator
# License: MIT
#
#------------------------------

QT += gui widgets

TARGET = MessageLog
TEMPLATE = app

SOURCES += \
    main.cpp \
    MainWindow.cpp \
    MessageList.cpp \
    Delegate.cpp

HEADERS += \
    MainWindow.h \
    MessageList.h \
    Delegate.h \
    Delegate_p.h

RESOURCES += \
    resources.qrc
