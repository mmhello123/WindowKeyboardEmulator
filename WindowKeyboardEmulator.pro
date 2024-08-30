QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    CloseDialog.cpp \
    GlobalHotkey.cpp \
    KeyPressEater.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    CloseDialog.h \
    GlobalHotkey.h \
    KeyPressEater.h \
    mainwindow.h

FORMS += \
    CloseDialog.ui \
    KeyPressEater.ui \
    mainwindow.ui

CONFIG += link_pch_by_file
LIBS += -luser32

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc
