QT += quick

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
QMAKE_LFLAGS += -Wl,-rpath,"'/opt/test/lib'"

LIBS += -lclientCommon
LIBS += -L/opt/test/lib
INCLUDEPATH += /opt/test/include/

PKG_CONFIG_PATH = $PKG_CONFIG_PATH:/opt/test/lib/pkgconfig
CONFIG += link_pkgconfig
#PKGCONFIG += giomm-2.4
#PKGCONFIG += glibmm-2.4
#PKGCONFIG += glib-2.0
PKGCONFIG += /opt/test/lib/pkgconfig/gdbusCodegenGlibmm.pc

SOURCES += \
        main.cpp \
        genCodeBridge.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/test/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    genCodeBridge.h

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../../../../opt/test/lib/release/ -lclientCommon
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../../../../opt/test/lib/debug/ -lclientCommon
else:unix: LIBS += -L$$PWD/../../../../../../../opt/test/lib/ -lclientCommon

INCLUDEPATH += $$PWD/../../../../../../../opt/test/include
DEPENDPATH += $$PWD/../../../../../../../opt/test/include
