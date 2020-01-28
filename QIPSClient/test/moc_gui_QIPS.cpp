/****************************************************************************
** Meta object code from reading C++ file 'gui_QIPS.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "gui_QIPS.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'gui_QIPS.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_guiQIPS_t {
    QByteArrayData data[17];
    char stringdata0[214];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_guiQIPS_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_guiQIPS_t qt_meta_stringdata_guiQIPS = {
    {
QT_MOC_LITERAL(0, 0, 7), // "guiQIPS"
QT_MOC_LITERAL(1, 8, 10), // "blockNewIp"
QT_MOC_LITERAL(2, 19, 0), // ""
QT_MOC_LITERAL(3, 20, 12), // "reportErrors"
QT_MOC_LITERAL(4, 33, 17), // "updateBlockedList"
QT_MOC_LITERAL(5, 51, 10), // "renewEntry"
QT_MOC_LITERAL(6, 62, 11), // "removeEntry"
QT_MOC_LITERAL(7, 74, 9), // "moveEntry"
QT_MOC_LITERAL(8, 84, 17), // "connectedToServer"
QT_MOC_LITERAL(9, 102, 18), // "processServerReply"
QT_MOC_LITERAL(10, 121, 11), // "std::string"
QT_MOC_LITERAL(11, 133, 5), // "reply"
QT_MOC_LITERAL(12, 139, 14), // "searchForEntry"
QT_MOC_LITERAL(13, 154, 15), // "removeConfirmed"
QT_MOC_LITERAL(14, 170, 13), // "moveConfirmed"
QT_MOC_LITERAL(15, 184, 14), // "renewConfirmed"
QT_MOC_LITERAL(16, 199, 14) // "blockConfirmed"

    },
    "guiQIPS\0blockNewIp\0\0reportErrors\0"
    "updateBlockedList\0renewEntry\0removeEntry\0"
    "moveEntry\0connectedToServer\0"
    "processServerReply\0std::string\0reply\0"
    "searchForEntry\0removeConfirmed\0"
    "moveConfirmed\0renewConfirmed\0"
    "blockConfirmed"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_guiQIPS[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   79,    2, 0x0a /* Public */,
       3,    0,   80,    2, 0x0a /* Public */,
       4,    0,   81,    2, 0x0a /* Public */,
       5,    0,   82,    2, 0x0a /* Public */,
       6,    0,   83,    2, 0x0a /* Public */,
       7,    0,   84,    2, 0x0a /* Public */,
       8,    0,   85,    2, 0x0a /* Public */,
       9,    1,   86,    2, 0x0a /* Public */,
      12,    0,   89,    2, 0x0a /* Public */,
      13,    0,   90,    2, 0x0a /* Public */,
      14,    0,   91,    2, 0x0a /* Public */,
      15,    0,   92,    2, 0x0a /* Public */,
      16,    0,   93,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 10,   11,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void guiQIPS::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        guiQIPS *_t = static_cast<guiQIPS *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->blockNewIp(); break;
        case 1: _t->reportErrors(); break;
        case 2: _t->updateBlockedList(); break;
        case 3: _t->renewEntry(); break;
        case 4: _t->removeEntry(); break;
        case 5: _t->moveEntry(); break;
        case 6: _t->connectedToServer(); break;
        case 7: _t->processServerReply((*reinterpret_cast< std::string(*)>(_a[1]))); break;
        case 8: _t->searchForEntry(); break;
        case 9: _t->removeConfirmed(); break;
        case 10: _t->moveConfirmed(); break;
        case 11: _t->renewConfirmed(); break;
        case 12: _t->blockConfirmed(); break;
        default: ;
        }
    }
}

const QMetaObject guiQIPS::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_guiQIPS.data,
      qt_meta_data_guiQIPS,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *guiQIPS::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *guiQIPS::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_guiQIPS.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "Ui::QIPSbox"))
        return static_cast< Ui::QIPSbox*>(this);
    return QDialog::qt_metacast(_clname);
}

int guiQIPS::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 13;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
