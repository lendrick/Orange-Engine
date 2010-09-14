/****************************************************************************
** Meta object code from reading C++ file 'tileselect.h'
**
** Created: Mon Sep 13 20:33:47 2010
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../qrpglib/tileselect.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'tileselect.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_TileBox[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      11,    9,    8,    8, 0x05,
      29,    8,    8,    8, 0x05,

 // slots: signature, parameters, type, tag, flags
      46,    8,    8,    8, 0x0a,
      61,    8,    8,    8, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_TileBox[] = {
    "TileBox\0\0,\0SetRange(int,int)\0"
    "TileChanged(int)\0SetScroll(int)\0"
    "SetSelected(int)\0"
};

const QMetaObject TileBox::staticMetaObject = {
    { &QGLWidget::staticMetaObject, qt_meta_stringdata_TileBox,
      qt_meta_data_TileBox, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &TileBox::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *TileBox::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *TileBox::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_TileBox))
        return static_cast<void*>(const_cast< TileBox*>(this));
    return QGLWidget::qt_metacast(_clname);
}

int TileBox::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGLWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: SetRange((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 1: TileChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: SetScroll((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: SetSelected((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void TileBox::SetRange(int _t1, int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void TileBox::TileChanged(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
static const uint qt_meta_data_TileSelect[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_TileSelect[] = {
    "TileSelect\0\0SetTiles(int)\0"
};

const QMetaObject TileSelect::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_TileSelect,
      qt_meta_data_TileSelect, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &TileSelect::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *TileSelect::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *TileSelect::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_TileSelect))
        return static_cast<void*>(const_cast< TileSelect*>(this));
    return QWidget::qt_metacast(_clname);
}

int TileSelect::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: SetTiles((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 1;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
