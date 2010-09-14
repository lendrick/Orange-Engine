/****************************************************************************
** Meta object code from reading C++ file 'talkbox.h'
**
** Created: Mon Sep 13 20:33:57 2010
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../qrpglib/talkbox.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'talkbox.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_TalkBox[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
       9,    8,    8,    8, 0x05,

 // slots: signature, parameters, type, tag, flags
      17,    8,    8,    8, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_TalkBox[] = {
    "TalkBox\0\0start()\0next()\0"
};

const QMetaObject TalkBox::staticMetaObject = {
    { &ImageFrame::staticMetaObject, qt_meta_stringdata_TalkBox,
      qt_meta_data_TalkBox, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &TalkBox::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *TalkBox::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *TalkBox::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_TalkBox))
        return static_cast<void*>(const_cast< TalkBox*>(this));
    return ImageFrame::qt_metacast(_clname);
}

int TalkBox::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = ImageFrame::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: start(); break;
        case 1: next(); break;
        default: ;
        }
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void TalkBox::start()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
