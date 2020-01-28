TEMPLATE               = app
OBJECTS_DIR            = obj
MOC_DIR                = moc
RESOURCES              = qips.qrc
QT                    += network gui widgets core

mac: {
CONFIG		      += debug_and_release build_all
CONFIG                -=app_bundle
CONFIG                +=console
}

unix:!mac {
CONFIG                += static release
LIBS		      += -lGLdispatch
}

win32 {
CONFIG                += static release
DEFINES               += 
}

CONFIG(debug, debug|release) {
                TARGET = QIPS_debug
 } else {
                TARGET = QIPS
 }


APPHEADERS +=  
APPSOURCES += app_main.cpp 

FORMS       = QIPS.ui confirmChange.ui login.ui

GUIHEADERS += gui_QIPS.h gui_confirmChange.h gui_login.h
GUISOURCES += gui_QIPS.cpp gui_confirmChange.cpp gui_login.cpp

NETHEADERS += net_client.h
NETSOURCES += net_client.cpp

XMLHEADERS += 
XMLSOURCES += 

HEADERS += $$APPHEADERS $$NETHEADERS $$XMLHEADERS $$GUIHEADERS $$SQLHEADERS
SOURCES += $$APPSOURCES $$NETSOURCES $$XMLSOURCES $$GUISOURCES $$SQLSOURCES
