#-------------------------------------------------
#
# Project created by QtCreator 2018-08-18T17:07:19
#
#-------------------------------------------------

QT       += core gui widgets

TARGET = NVR
#TEMPLATE = lib

# CONFIG += staticlib   #   Static Library

#DEFINES += NVR_LIBRARY

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS GST_USE

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
			NVR.cpp \
			mainwindow.cpp \
			devwindow.cpp \
			testwindow.cpp

#			NVREnv.cpp \
#			gstMgr.cpp \

HEADERS += \
			NVR.h \
			mainwindow.h \
			devwindow.h \
			testwindow.h

#			NVREnv.h \
#			gstDefine.h \
#			gstMgr.h \
					
################################################################
# Include Path
INCLUDEPATH += $$PWD/../../ItLib/include $$PWD/../../ItLibSMRT/include $$PWD/../../ItQLib/include
DEPENDPATH += $$PWD/../../ItLib/include $$PWD/../../ItLibSMRT/include $$PWD/../../ItQLib/include

# Include Path ( Local )
INCLUDEPATH += $$PWD $$PWD/../ $$PWD/Env $$PWD/UI
DEPENDPATH 	+= $$PWD $$PWD/../ $$PWD/Env $$PWD/UI


message($$QMAKESPEC)

linux-g++ {

    message("linux-g++ config ( x86 )")

}
linux-g++-64 {

    message("linux-g++-64 config ( x86_64 )")
	
}

linux-oe-g++ {

################################################################
#		Link Option
# https://gcc.gnu.org/onlinedocs/gcc/Optimize-Options.html
# -O1 : Optimize. ( level 1 )

# https://gcc.gnu.org/onlinedocs/gcc/Link-Options.html
# -s : Remove all symbol table and relocation information from the executable.
#	-s : debug symbol 정보 삭제 binary size ( 2,996,920 byte -> 163,124 byte )
QMAKE_LFLAGS_RELEASE = -Wl,-O1,-s
################################################################

################################################################
# Target - arm compile ( arm-poky-gnueabi-g++ )
    message("arm-poky-linux-gnueabi-g++ config")

	LIBS += -L$$PWD/../../ItLib/arm/lib/ -lit -L$$PWD/../../ItLibSMRT/arm/lib/ -lsmrt -L$$PWD/../../ItQLib/arm/lib/ -lItQLib
	
	INCLUDEPATH += $$PWD/../ItLib/include/linux

    INCLUDEPATH+=$(SDKTARGETSYSROOT)/usr/include/glib-2.0
    INCLUDEPATH+=$(SDKTARGETSYSROOT)/usr/lib/glib-2.0/include
    INCLUDEPATH+=$(SDKTARGETSYSROOT)/usr/lib/gstreamer-1.0/include
    INCLUDEPATH+=$(SDKTARGETSYSROOT)/usr/include/gstreamer-1.0
    LIBS+=-lgstreamer-1.0 -lgobject-2.0 -lglib-2.0 -lasound
	
################################################################
# 빌드 후 이벤트 : post_build_event.sh $$PWD $$OUT_PWD
#   헤더파일 copy
    QMAKE_POST_LINK = $$PWD/post_build_event.sh $$PWD $$OUT_PWD arm
################################################################
}
else: linux {
################################################################
# Desktop - compile
    message("linux host config")

	LIBS += -L$$PWD/../../ItLib/x86_64/lib/ -lit -L$$PWD/../../ItLibSMRT/x86_64/lib/ -lsmrt -L$$PWD/../../ItQLib/x86_64/lib/ -lItQLib
	
	INCLUDEPATH += /usr/include/gstreamer-1.0/ /usr/include/glib-2.0/ /usr/lib/x86_64-linux-gnu/glib-2.0/include /usr/lib/x86_64-linux-gnu/gstreamer-1.0/include/
	DEPENDPATH += /usr/include/gstreamer-1.0/ /usr/include/glib-2.0/ /usr/lib/x86_64-linux-gnu/glib-2.0/include /usr/lib/x86_64-linux-gnu/gstreamer-1.0/include/

	LIBS+=-lgstreamer-1.0 -lgobject-2.0 -lglib-2.0

	################################################################
    QMAKE_POST_LINK = $$PWD/post_build_event.sh $$PWD $$OUT_PWD x86_64

}


linux {
    message("linux config")

	INCLUDEPATH += $$PWD/../../ItLib/include/linux
}

win32 {
    message("windows config")

	# UI - PC Platform
	DEFINES += QT_UI_USE

	#no_plugin_name_prefix : lib Prefix Remove
    CONFIG += no_plugin_name_prefix

    target.path = $$PWD/
    INSTALLS += target
	
	contains(QT_ARCH, i386) {
		message("32-bit")
	
		DEFINES += UNICODE _UNICODE
	
		CONFIG(Debug, Debug|Release) {
			LIBS += -L$$PWD/../../ItLib/Debug/ -lItLib -L$$PWD/../../ItLibSMRT/Debug/ -lItLibSMRT -L$$PWD/../../ItQLib/Debug/ -lItQLib
			DESTDIR = $$PWD/../Debug
		}
		else {
			LIBS += -L$$PWD/../../ItLib/Release/ -lItLib -L$$PWD/../../ItLibSMRT/Release/ -lItLibSMRT -L$$PWD/../../ItQLib/Release/ -lItQLib
			DESTDIR = $$PWD/../Release
		}
	
	} else {
		message("64-bit")
	
		DEFINES += UNICODE _UNICODE
	
	#    win32:CONFIG(Debug, Debug|Release):   message("Debug - Config")
	#    else:win32:CONFIG(Release, Debug|Release): message("Release - Config")
	
		INCLUDEPATH += $(GSTREAMER_1_0_ROOT_X86_64)\include $(GSTREAMER_1_0_ROOT_X86_64)\include\glib-2.0 $(GSTREAMER_1_0_ROOT_X86_64)\lib\glib-2.0\include $(GSTREAMER_1_0_ROOT_X86_64)\include\gstreamer-1.0
		DEPENDPATH += $(GSTREAMER_1_0_ROOT_X86_64)\include $(GSTREAMER_1_0_ROOT_X86_64)\include\glib-2.0 $(GSTREAMER_1_0_ROOT_X86_64)\lib\glib-2.0\include $(GSTREAMER_1_0_ROOT_X86_64)\include\gstreamer-1.0

		LIBS += -L$(GSTREAMER_1_0_ROOT_X86_64)\lib -lglib-2.0 -lgobject-2.0 -lgstreamer-1.0 -lgstbase-1.0 -lgstvideo-1.0 -lgstplayer-1.0

		CONFIG(Debug, Debug|Release) {
			message("Debug")
			#LIBS += -L$$PWD/../../ItLib/x64/Debug/ -lItLib -L$$PWD/../../ItLibSMRT/x64/Debug/ -lItLibSMRT -L$$PWD/../../ItQLib/x64/Debug/ -lItQLib
			LIBS += -L$$PWD/../ItLib/x64/Debug/ -lItLib -L$$PWD/../ItLibSMRT/x64/Debug/ -lItLibSMRT
			DESTDIR = $$PWD/../x64/Debug
		}
		else {
			message("Release")
			#LIBS += -L$$PWD/../../ItLib/x64/Release/ -lItLib -L$$PWD/../../ItLibSMRT/x64/Release/ -lItLibSMRT -L$$PWD/../../ItQLib/x64/Release/ -lItQLib
			LIBS += -L$$PWD/../ItLib/x64/Release/ -lItLib -L$$PWD/../ItLibSMRT/x64/Release/ -lItLibSMRT
			DESTDIR = $$PWD/../x64/Release
		}
	}
	
################################################################
# 빌드 후 이벤트 : post_build_event.bat $$PWD $$OUT_PWD
#   헤더파일 copy
    QMAKE_POST_LINK = $$PWD/post_build_event.bat $$PWD $$OUT_PWD
################################################################
}

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
