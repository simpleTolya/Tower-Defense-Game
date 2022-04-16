QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    srcs/abstractfield.cpp \
	srcs/bullet.cpp \
	srcs/earthtower.cpp \
	srcs/earthtowerbutton.cpp \
	srcs/enemy.cpp \
	srcs/field.cpp \
	srcs/firetower.cpp \
	srcs/firetowerbutton.cpp \
	srcs/icetower.cpp \
	srcs/icetowerbutton.cpp \
	srcs/main.cpp \
	srcs/mainwindow.cpp \
	srcs/tower.cpp \
	srcs/towerbutton.cpp

HEADERS += \
    headers/abstractfield.h \
	headers/bullet.h \
	headers/earthtower.h \
	headers/earthtowerbutton.h \
	headers/enemy.h \
	headers/field.h \
	headers/firetower.h \
	headers/firetowerbutton.h \
	headers/icetower.h \
	headers/icetowerbutton.h \
	headers/mainwindow.h \
	headers/tower.h \
	headers/towerbutton.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc
