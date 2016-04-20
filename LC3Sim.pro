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
  INCLUDEPATH += "pylc3/inc/" "inc/" "/usr/include/pylc3"
#  SOURCES += "pylc3/src/simulator.cpp"

  #LIBS += -L"$(PYTHON_PATH)/lib/python$(PYTHON_VERSION)/config" -lutil
#  LIBS += -L/usr/lib/python2.7/dist-packages/
  LIBS += -lpython2.7 -lutil -lboost_python -lboost_system -lpylc3

  #copy over some other important files
  EXTRA_BINFILES += \
    pylc3.so \
    lc3os.obj
  for(FILE,EXTRA_BINFILES){
    system(cp $${PWD}/$${FILE} $${OUT_PWD})
  }
  system(cp -rf $${PWD}/help $${OUT_PWD})

  SOURCES += $$files(src/*.cpp)
  HEADERS += $$files(inc/*.h) \
              $$files(inc/*.hpp) $$files(pylc3/inc/*.h) $$files(pylc3/inc/*.hpp)
  RESOURCES = qdarkstyle/style.qrc
}



FORMS += *.ui
