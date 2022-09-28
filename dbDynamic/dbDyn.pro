QT -= gui
QT += sql

TEMPLATE = lib
DEFINES += DBDYN_LIBRARY

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    c_a.cpp \
    tm_messages.cpp \
    types.cpp

HEADERS += \
    connection.h \
    dbDyn_global.h \
    db_library.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target


unix:QMAKE_CFLAGS_WARN_ON += -Wno-deprecated-copy
unix:QMAKE_CXXFLAGS_WARN_ON += -Wno-deprecated-copy
