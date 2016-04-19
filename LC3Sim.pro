#-------------------------------------------------
#
# Project created by QtCreator 2015-02-13T09:27:19
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = LC3Sim
TEMPLATE = app

CONFIG += c++11
LIBS += -Wl,-E -lpython2.7
QT += widgets
DEFINES += USE_POPUP_COMPLETER
unix {
  INCLUDEPATH += "/usr/include/python2.7/"
  #LIBS += -L"$(PYTHON_PATH)/lib/python$(PYTHON_VERSION)/config" -lutil
  LIBS += -lpython2.7 -lutil -lboost_python -lboost_system
  EXTRA_BINFILES += \
    pylc3.so \
    lc3os.obj
  for(FILE,EXTRA_BINFILES){
    system(cp $${FILE} $${OUT_PWD})
  }
  system(cp -rf help $${OUT_PWD})
}

#SOURCES += main.cpp\
#        mainwindow.cpp \
#    lc3sim.cpp

SOURCES += *.cpp


#HEADERS  += mainwindow.h \
#    lc3sim.h

#FORMS    += mainwindow.ui

HEADERS += *.h \
        *.hpp

FORMS += *.ui
RESOURCES = qdarkstyle/style.qrc
