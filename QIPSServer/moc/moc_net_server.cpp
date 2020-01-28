/****************************************************************************
** Meta object code from reading C++ file 'net_server.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../net_server.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QList>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'net_server.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_netServer_t {
    QByteArrayData data[20];
    char stringdata0[268];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_netServer_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_netServer_t qt_meta_stringdata_netServer = {
    {
QT_MOC_LITERAL(0, 0, 9), // "netServer"
QT_MOC_LITERAL(1, 10, 17), // "receiveConnection"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 16), // "receiveReadyRead"
QT_MOC_LITERAL(4, 46, 15), // "webDisconnected"
QT_MOC_LITERAL(5, 62, 18), // "incomingConnection"
QT_MOC_LITERAL(6, 81, 7), // "qintptr"
QT_MOC_LITERAL(7, 89, 16), // "socketDescriptor"
QT_MOC_LITERAL(8, 106, 9), // "sslErrors"
QT_MOC_LITERAL(9, 116, 16), // "QList<QSslError>"
QT_MOC_LITERAL(10, 133, 6), // "errors"
QT_MOC_LITERAL(11, 140, 17), // "removalSuccessful"
QT_MOC_LITERAL(12, 158, 17), // "renewalSuccessful"
QT_MOC_LITERAL(13, 176, 14), // "moveSuccessful"
QT_MOC_LITERAL(14, 191, 13), // "addSuccessful"
QT_MOC_LITERAL(15, 205, 1), // "i"
QT_MOC_LITERAL(16, 207, 14), // "processStarted"
QT_MOC_LITERAL(17, 222, 16), // "reportProcErrors"
QT_MOC_LITERAL(18, 239, 22), // "QProcess::ProcessError"
QT_MOC_LITERAL(19, 262, 5) // "error"

    },
    "netServer\0receiveConnection\0\0"
    "receiveReadyRead\0webDisconnected\0"
    "incomingConnection\0qintptr\0socketDescriptor\0"
    "sslErrors\0QList<QSslError>\0errors\0"
    "removalSuccessful\0renewalSuccessful\0"
    "moveSuccessful\0addSuccessful\0i\0"
    "processStarted\0reportProcErrors\0"
    "QProcess::ProcessError\0error"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_netServer[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   69,    2, 0x0a /* Public */,
       3,    0,   70,    2, 0x0a /* Public */,
       4,    0,   71,    2, 0x0a /* Public */,
       5,    1,   72,    2, 0x0a /* Public */,
       8,    1,   75,    2, 0x0a /* Public */,
      11,    0,   78,    2, 0x0a /* Public */,
      12,    0,   79,    2, 0x0a /* Public */,
      13,    0,   80,    2, 0x0a /* Public */,
      14,    1,   81,    2, 0x0a /* Public */,
      16,    0,   84,    2, 0x0a /* Public */,
      17,    1,   85,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 6,    7,
    QMetaType::Void, 0x80000000 | 9,   10,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   15,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 18,   19,

       0        // eod
};

void netServer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        netServer *_t = static_cast<netServer *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->receiveConnection(); break;
        case 1: _t->receiveReadyRead(); break;
        case 2: _t->webDisconnected(); break;
        case 3: _t->incomingConnection((*reinterpret_cast< qintptr(*)>(_a[1]))); break;
        case 4: _t->sslErrors((*reinterpret_cast< QList<QSslError>(*)>(_a[1]))); break;
        case 5: _t->removalSuccessful(); break;
        case 6: _t->renewalSuccessful(); break;
        case 7: _t->moveSuccessful(); break;
        case 8: _t->addSuccessful((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: _t->processStarted(); break;
        case 10: _t->reportProcErrors((*reinterpret_cast< QProcess::ProcessError(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 4:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QList<QSslError> >(); break;
            }
            break;
        }
    }
}

const QMetaObject netServer::staticMetaObject = {
    { &QTcpServer::staticMetaObject, qt_meta_stringdata_netServer.data,
      qt_meta_data_netServer,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *netServer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *netServer::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_netServer.stringdata0))
        return static_cast<void*>(this);
    return QTcpServer::qt_metacast(_clname);
}

int netServer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QTcpServer::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
