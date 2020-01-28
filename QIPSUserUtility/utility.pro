TEMPLATE               = app
OBJECTS_DIR            = obj
MOC_DIR                = moc
RESOURCES              = qips.qrc
QT                    += network core

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
                TARGET = utility_debug
 } else {
                TARGET = utility
 }


APPHEADERS +=  
APPSOURCES += app_main.cpp 

FORMS       = 

GUIHEADERS += 
GUISOURCES += 

NETHEADERS += qips_utility.h
NETSOURCES += qips_utility.cpp

XMLHEADERS += 
XMLSOURCES += 

HEADERS += $$APPHEADERS $$NETHEADERS $$XMLHEADERS $$GUIHEADERS $$SQLHEADERS
SOURCES += $$APPSOURCES $$NETSOURCES $$XMLSOURCES $$GUISOURCES $$SQLSOURCES
