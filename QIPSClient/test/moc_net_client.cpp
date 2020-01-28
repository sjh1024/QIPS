/****************************************************************************
** Meta object code from reading C++ file 'net_client.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "net_client.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QList>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'net_client.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_netClient_t {
    QByteArrayData data[11];
    char stringdata0[120];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_netClient_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_netClient_t qt_meta_stringdata_netClient = {
    {
QT_MOC_LITERAL(0, 0, 9), // "netClient"
QT_MOC_LITERAL(1, 10, 9), // "sentReply"
QT_MOC_LITERAL(2, 20, 0), // ""
QT_MOC_LITERAL(3, 21, 11), // "std::string"
QT_MOC_LITERAL(4, 33, 5), // "reply"
QT_MOC_LITERAL(5, 39, 19), // "establishConnection"
QT_MOC_LITERAL(6, 59, 12), // "readResponse"
QT_MOC_LITERAL(7, 72, 12), // "displayError"
QT_MOC_LITERAL(8, 85, 16), // "QList<QSslError>"
QT_MOC_LITERAL(9, 102, 5), // "error"
QT_MOC_LITERAL(10, 108, 11) // "isEncrypted"

    },
    "netClient\0sentReply\0\0std::string\0reply\0"
    "establishConnection\0readResponse\0"
    "displayError\0QList<QSslError>\0error\0"
    "isEncrypted"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_netClient[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   39,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    0,   42,    2, 0x0a /* Public */,
       6,    0,   43,    2, 0x0a /* Public */,
       7,    1,   44,    2, 0x0a /* Public */,
      10,    0,   47,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 8,    9,
    QMetaType::Void,

       0        // eod
};

void netClient::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        netClient *_t = static_cast<netClient *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sentReply((*reinterpret_cast< std::string(*)>(_a[1]))); break;
        case 1: _t->establishConnection(); break;
        case 2: _t->readResponse(); break;
        case 3: _t->displayError((*reinterpret_cast< QList<QSslError>(*)>(_a[1]))); break;
        case 4: _t->isEncrypted(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 3:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QList<QSslError> >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (netClient::*_t)(std::string );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&netClient::sentReply)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject netClient::staticMetaObject = {
    { &QSslSocket::staticMetaObject, qt_meta_stringdata_netClient.data,
      qt_meta_data_netClient,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *netClient::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *netClient::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_netClient.stringdata0))
        return static_cast<void*>(this);
    return QSslSocket::qt_metacast(_clname);
}

int netClient::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QSslSocket::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void netClient::sentReply(std::string _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
