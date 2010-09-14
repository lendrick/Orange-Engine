/****************************************************************************
** Meta object code from reading C++ file 'newlayerdialog.h'
**
** Created: Mon Sep 13 20:36:08 2010
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../qrpglib/newlayerdialog.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'newlayerdialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_NewLayerDialog[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      20,   15,   16,   15, 0x0a,
      27,   15,   15,   15, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_NewLayerDialog[] = {
    "NewLayerDialog\0\0int\0exec()\0submit()\0"
};

const QMetaObject NewLayerDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_NewLayerDialog,
      qt_meta_data_NewLayerDialog, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &NewLayerDialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *NewLayerDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *NewLayerDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_NewLayerDialog))
        return static_cast<void*>(const_cast< NewLayerDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int NewLayerDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: { int _r = exec();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 1: submit(); break;
        default: ;
        }
        _id -= 2;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
