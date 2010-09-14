/****************************************************************************
** Meta object code from reading C++ file 'qrpgconsole.h'
**
** Created: Mon Sep 13 20:34:45 2010
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../qrpglib/qrpgconsole.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qrpgconsole.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QRPGConsole[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      15,   13,   12,   12, 0x0a,
      31,   12,   12,   12, 0x0a,
      39,   12,   12,   12, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_QRPGConsole[] = {
    "QRPGConsole\0\0s\0append(QString)\0clear()\0"
    "execute()\0"
};

const QMetaObject QRPGConsole::staticMetaObject = {
    { &QFrame::staticMetaObject, qt_meta_stringdata_QRPGConsole,
      qt_meta_data_QRPGConsole, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QRPGConsole::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QRPGConsole::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QRPGConsole::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QRPGConsole))
        return static_cast<void*>(const_cast< QRPGConsole*>(this));
    return QFrame::qt_metacast(_clname);
}

int QRPGConsole::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QFrame::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: append((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: clear(); break;
        case 2: execute(); break;
        default: ;
        }
        _id -= 3;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
