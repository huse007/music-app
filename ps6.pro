#-------------------------------------------------
#
# Project created by QtCreator 2017-01-01T12:45:59
#
#-------------------------------------------------

QT       += core gui printsupport svg

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ps6
TEMPLATE = app


SOURCES += configdialog.cpp\
    main.cpp\
nash.cpp\
nashville.cpp \
    widget.cpp \
    rectangle.cpp \
    title.cpp \
    logo.cpp \
    cursor.cpp \
    page.cpp \
    note.cpp \
    legato.cpp \
    slide.cpp \
    settings.cpp \
    #nash.cpp \
    chord.cpp \
    symboldialog.cpp \
    line.cpp \
    element.cpp


HEADERS  += global.h \
    configdialog.h \
    widget.h \
    rectangle.h \
    title.h \
    logo.h \
    cursor.h \
    page.h \
    note.h \
    legato.h \
    slide.h \
    settings.h \
nash.h \
    nashville.h \
    #nash.h \
    chord.h \
    symboldialog.h \
    line.h \
    element.h

DISTFILES +=

RESOURCES += \
    resources.qrc
