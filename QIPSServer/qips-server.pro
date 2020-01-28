TEMPLATE               = app
OBJECTS_DIR            = obj
MOC_DIR                = moc
RESOURCES              = qips.qrc
QT                    += network sql testlib

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
                TARGET = qips_debug
 } else {
                TARGET = qips
 }


APPHEADERS +=  
APPSOURCES += app_main.cpp 

FORMS       = 

GUIHEADERS += 
GUISOURCES += 

NETHEADERS += net_server.h
NETSOURCES += net_server.cpp

XMLHEADERS += 
XMLSOURCES += 

SQLHEADERS += 
SQLSOURCES += 

HEADERS += $$APPHEADERS $$NETHEADERS $$XMLHEADERS $$GUIHEADERS $$SQLHEADERS
SOURCES += $$APPSOURCES $$NETSOURCES $$XMLSOURCES $$GUISOURCES $$SQLSOURCES
