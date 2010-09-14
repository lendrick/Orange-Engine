/****************************************************************************
** Meta object code from reading C++ file 'scriptutils.h'
**
** Created: Mon Sep 13 20:34:38 2010
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../qrpglib/scriptutils.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'scriptutils.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ScriptUtils[] = {

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
      35,   13,   12,   12, 0x0a,
      63,   13,   50,   12, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_ScriptUtils[] = {
    "ScriptUtils\0\0s\0messageBox(QString)\0"
    "print(QString)\0QScriptValue\0"
    "getEntity(QString)\0"
};

const QMetaObject ScriptUtils::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_ScriptUtils,
      qt_meta_data_ScriptUtils, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ScriptUtils::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ScriptUtils::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ScriptUtils::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ScriptUtils))
        return static_cast<void*>(const_cast< ScriptUtils*>(this));
    if (!strcmp(_clname, "QScriptable"))
        return static_cast< QScriptable*>(const_cast< ScriptUtils*>(this));
    return QObject::qt_metacast(_clname);
}

int ScriptUtils::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: messageBox((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: print((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: { QScriptValue _r = getEntity((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QScriptValue*>(_a[0]) = _r; }  break;
        default: ;
        }
        _id -= 3;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
