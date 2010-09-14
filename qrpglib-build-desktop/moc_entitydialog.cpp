/****************************************************************************
** Meta object code from reading C++ file 'entitydialog.h'
**
** Created: Mon Sep 13 20:37:41 2010
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../qrpglib/entitydialog.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'entitydialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_CoordinateWidget[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

static const char qt_meta_stringdata_CoordinateWidget[] = {
    "CoordinateWidget\0"
};

const QMetaObject CoordinateWidget::staticMetaObject = {
    { &QFrame::staticMetaObject, qt_meta_stringdata_CoordinateWidget,
      qt_meta_data_CoordinateWidget, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &CoordinateWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *CoordinateWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *CoordinateWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CoordinateWidget))
        return static_cast<void*>(const_cast< CoordinateWidget*>(this));
    return QFrame::qt_metacast(_clname);
}

int CoordinateWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QFrame::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
static const uint qt_meta_data_EntityDialog[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      18,   13,   14,   13, 0x0a,
      25,   13,   13,   13, 0x0a,
      37,   13,   13,   13, 0x0a,
      49,   13,   13,   13, 0x0a,
      67,   13,   13,   13, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_EntityDialog[] = {
    "EntityDialog\0\0int\0exec()\0addScript()\0"
    "delScript()\0deleteScript(int)\0"
    "updateStateSelect()\0"
};

const QMetaObject EntityDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_EntityDialog,
      qt_meta_data_EntityDialog, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &EntityDialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *EntityDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *EntityDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_EntityDialog))
        return static_cast<void*>(const_cast< EntityDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int EntityDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: { int _r = exec();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 1: addScript(); break;
        case 2: delScript(); break;
        case 3: deleteScript((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: updateStateSelect(); break;
        default: ;
        }
        _id -= 5;
    }
    return _id;
}
static const uint qt_meta_data_ScriptTab[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

static const char qt_meta_stringdata_ScriptTab[] = {
    "ScriptTab\0"
};

const QMetaObject ScriptTab::staticMetaObject = {
    { &QFrame::staticMetaObject, qt_meta_stringdata_ScriptTab,
      qt_meta_data_ScriptTab, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ScriptTab::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ScriptTab::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ScriptTab::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ScriptTab))
        return static_cast<void*>(const_cast< ScriptTab*>(this));
    return QFrame::qt_metacast(_clname);
}

int ScriptTab::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QFrame::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
QT_END_MOC_NAMESPACE
