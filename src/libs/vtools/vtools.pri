include(dialogs/dialogs.pri)
include(tools/tools.pri)
include(visualization/visualization.pri)
include(undocommands/undocommands.pri)

# ADD TO EACH PATH $$PWD VARIABLE!!!!!!
# This need for correct working file translations.pro

HEADERS += \
    $$PWD/stable.h

*msvc*:SOURCES += $$PWD/stable.cpp

