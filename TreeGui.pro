QT += core gui

CONFIG += c++11

SOURCES += main.cpp \
    gui_func.cpp \
    node.cpp \
    complex.hpp \
    tree.cpp 

LIBS += -lsfml-graphics -lsfml-window -lsfml-system
