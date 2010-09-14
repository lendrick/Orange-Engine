/****************************************************************************
** Meta object code from reading C++ file 'npc.h'
**
** Created: Mon Sep 13 20:35:34 2010
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../qrpglib/npc.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'npc.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Npc[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      15,    5,    4,    4, 0x0a,
      51,   47,    4,    4, 0x2a,
      76,    5,    4,    4, 0x0a,
     110,   47,    4,    4, 0x2a,
     139,  137,    4,    4, 0x0a,
     156,  154,    4,    4, 0x0a,
     177,    4,    4,    4, 0x0a,
     198,    4,  190,    4, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_Npc[] = {
    "Npc\0\0x,y,speed\0queueMove(double,double,double)\0"
    "x,y\0queueMove(double,double)\0"
    "queueMoveTo(double,double,double)\0"
    "queueMoveTo(double,double)\0w\0"
    "queueWait(int)\0s\0queueScript(QString)\0"
    "clearQueue()\0Entity*\0clone()\0"
};

const QMetaObject Npc::staticMetaObject = {
    { &Entity::staticMetaObject, qt_meta_stringdata_Npc,
      qt_meta_data_Npc, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Npc::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Npc::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Npc::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Npc))
        return static_cast<void*>(const_cast< Npc*>(this));
    return Entity::qt_metacast(_clname);
}

int Npc::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = Entity::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: queueMove((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2])),(*reinterpret_cast< double(*)>(_a[3]))); break;
        case 1: queueMove((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2]))); break;
        case 2: queueMoveTo((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2])),(*reinterpret_cast< double(*)>(_a[3]))); break;
        case 3: queueMoveTo((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2]))); break;
        case 4: queueWait((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: queueScript((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 6: clearQueue(); break;
        case 7: { Entity* _r = clone();
            if (_a[0]) *reinterpret_cast< Entity**>(_a[0]) = _r; }  break;
        default: ;
        }
        _id -= 8;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
