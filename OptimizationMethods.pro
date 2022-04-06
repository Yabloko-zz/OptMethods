QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11
CONFIG += qwt

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    graphics.cpp \
    main.cpp \
    mainwindow.cpp \
    optmath.cpp \
    qwt_graphx.cpp

HEADERS += \
    graphics.h \
    mainwindow.h \
    optmath.h \
    qwt_graphx.h

FORMS += \
    mainwindow.ui

INCLUDEPATH += C:/qwt-6.1.6/include

LIBS += -L$$PWD/qwt-6.1.6/lib/
LIBS += -lqwt
LIBS += -lqwtd

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
