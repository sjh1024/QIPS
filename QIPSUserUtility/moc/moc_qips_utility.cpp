/****************************************************************************
** Meta object code from reading C++ file 'qips_utility.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../qips_utility.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QList>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qips_utility.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_QIPSUtility_t {
    QByteArrayData data[9];
    char stringdata0[116];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_QIPSUtility_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_QIPSUtility_t qt_meta_stringdata_QIPSUtility = {
    {
QT_MOC_LITERAL(0, 0, 11), // "QIPSUtility"
QT_MOC_LITERAL(1, 12, 19), // "establishConnection"
QT_MOC_LITERAL(2, 32, 0), // ""
QT_MOC_LITERAL(3, 33, 18), // "readServerResponse"
QT_MOC_LITERAL(4, 52, 13), // "displayErrors"
QT_MOC_LITERAL(5, 66, 16), // "QList<QSslError>"
QT_MOC_LITERAL(6, 83, 6), // "errors"
QT_MOC_LITERAL(7, 90, 11), // "isEncrypted"
QT_MOC_LITERAL(8, 102, 13) // "processChecks"

    },
    "QIPSUtility\0establishConnection\0\0"
    "readServerResponse\0displayErrors\0"
    "QList<QSslError>\0errors\0isEncrypted\0"
    "processChecks"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QIPSUtility[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   39,    2, 0x0a /* Public */,
       3,    0,   40,    2, 0x0a /* Public */,
       4,    1,   41,    2, 0x0a /* Public */,
       7,    0,   44,    2, 0x0a /* Public */,
       8,    0,   45,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 5,    6,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void QIPSUtility::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        QIPSUtility *_t = static_cast<QIPSUtility *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->establishConnection(); break;
        case 1: _t->readServerResponse(); break;
        case 2: _t->displayErrors((*reinterpret_cast< QList<QSslError>(*)>(_a[1]))); break;
        case 3: _t->isEncrypted(); break;
        case 4: _t->processChecks(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 2:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QList<QSslError> >(); break;
            }
            break;
        }
    }
}

const QMetaObject QIPSUtility::staticMetaObject = {
    { &QSslSocket::staticMetaObject, qt_meta_stringdata_QIPSUtility.data,
      qt_meta_data_QIPSUtility,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *QIPSUtility::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QIPSUtility::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_QIPSUtility.stringdata0))
        return static_cast<void*>(this);
    return QSslSocket::qt_metacast(_clname);
}

int QIPSUtility::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
QT_WARNING_POP
QT_END_MOC_NAMESPACE
