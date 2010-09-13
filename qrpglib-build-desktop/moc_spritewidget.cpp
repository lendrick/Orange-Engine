/****************************************************************************
** Meta object code from reading C++ file 'spritewidget.h'
**
** Created: Mon Sep 13 13:41:29 2010
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../qrpglib/spritewidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'spritewidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_SpriteWidget[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: signature, parameters, type, tag, flags
      16,   14,   13,   13, 0x05,
      39,   14,   13,   13, 0x05,
      62,   13,   13,   13, 0x05,
      84,   13,   13,   13, 0x05,
     105,   13,   13,   13, 0x05,

 // slots: signature, parameters, type, tag, flags
     121,   13,   13,   13, 0x0a,
     128,   13,   13,   13, 0x0a,
     136,   13,   13,   13, 0x0a,
     143,   13,   13,   13, 0x0a,
     157,   13,   13,   13, 0x0a,
     171,   13,   13,   13, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_SpriteWidget[] = {
    "SpriteWidget\0\0,\0SetStateRange(int,int)\0"
    "SetFrameRange(int,int)\0SetFrameDuration(int)\0"
    "SetSelectedTile(int)\0updateTime(int)\0"
    "Play()\0Pause()\0Stop()\0SetState(int)\0"
    "SetFrame(int)\0updateDuration(int)\0"
};

const QMetaObject SpriteWidget::staticMetaObject = {
    { &QGLWidget::staticMetaObject, qt_meta_stringdata_SpriteWidget,
      qt_meta_data_SpriteWidget, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &SpriteWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *SpriteWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *SpriteWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SpriteWidget))
        return static_cast<void*>(const_cast< SpriteWidget*>(this));
    return QGLWidget::qt_metacast(_clname);
}

int SpriteWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGLWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: SetStateRange((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 1: SetFrameRange((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 2: SetFrameDuration((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: SetSelectedTile((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: updateTime((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: Play(); break;
        case 6: Pause(); break;
        case 7: Stop(); break;
        case 8: SetState((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: SetFrame((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 10: updateDuration((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 11;
    }
    return _id;
}

// SIGNAL 0
void SpriteWidget::SetStateRange(int _t1, int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void SpriteWidget::SetFrameRange(int _t1, int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void SpriteWidget::SetFrameDuration(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void SpriteWidget::SetSelectedTile(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void SpriteWidget::updateTime(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}
QT_END_MOC_NAMESPACE
