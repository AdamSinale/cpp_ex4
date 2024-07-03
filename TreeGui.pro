QT += core gui

CONFIG += c++11

SOURCES += main.cpp \
    gui_func.cpp \
    node.cpp \
    tree.cpp

LIBS += -lsfml-graphics -lsfml-window -lsfml-system
