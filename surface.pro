android|ios|winrt {
    error( "This example is not supported for android, ios, or winrt." )
}

!include( ../examples.pri ) {
    error( "Couldn't find the examples.pri file!" )
}

SOURCES += main.cpp \
           mainwindow.cpp \
           surfacegraph.cpp

HEADERS += surfacegraph.h \
    mainwindow.h

QT += widgets
QT += datavisualization

requires(qtConfig(combobox))

RESOURCES += surface.qrc

OTHER_FILES += doc/src/* \
               doc/images/*
