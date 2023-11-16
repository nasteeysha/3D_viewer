QT       += core gui opengl openglwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

win32 {
    LIBS = -lopengl32 -lglu32
}

include(gif_module/QtGifImage/src/gifimage/qtgifimage.pri)

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    glview.cpp \
    main.cpp \
    mainwindow.cpp \
    s21_objloader.c \
    stack.c \
    parser.c \
    secondary.c \
    transformations.c

HEADERS += \
    glview.h \
    mainwindow.h \
    s21_objloader.h \
    stack.h \
    transformations.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = ../../build
else: unix:!android: target.path = ../../build
!isEmpty(target.path): INSTALLS += target

DISTFILES +=
