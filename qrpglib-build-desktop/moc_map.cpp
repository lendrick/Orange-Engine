/****************************************************************************
** Meta object code from reading C++ file 'map.h'
**
** Created: Mon Sep 13 20:37:02 2010
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../qrpglib/map.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'map.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Map[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      30,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      12,   10,    5,    4, 0x0a,
      37,    4,   29,    4, 0x0a,
      62,   47,    4,    4, 0x0a,
     101,   91,   87,    4, 0x0a,
     122,    4,   87,    4, 0x0a,
     140,  134,   29,    4, 0x0a,
     169,  158,    4,    4, 0x0a,
     218,  195,   87,    4, 0x0a,
     271,  253,   87,    4, 0x2a,
     307,  298,   87,    4, 0x2a,
     334,  330,   87,    4, 0x2a,
     370,  352,    4,    4, 0x0a,
     418,  389,    4,    4, 0x0a,
     490,  466,    4,    4, 0x2a,
     545,  530,    4,    4, 0x2a,
     591,  581,    4,    4, 0x2a,
     622,  389,    4,    4, 0x0a,
     669,  466,    4,    4, 0x2a,
     708,  530,    4,    4, 0x2a,
     743,  581,    4,    4, 0x2a,
     773,  134,    4,    4, 0x0a,
     798,  790,    4,    4, 0x0a,
     840,  827,    4,    4, 0x0a,
     863,  827,    4,    4, 0x0a,
     891,  827,    4,    4, 0x0a,
     917,  827,    4,    4, 0x0a,
     948,  134,   87,    4, 0x0a,
     965,  134,   87,    4, 0x0a,
     987,    4,    4,    4, 0x0a,
     995,    4,    4,    4, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_Map[] = {
    "Map\0\0bool\0n\0SetName(QString)\0QString\0"
    "GetName()\0layer,x,y,tile\0"
    "SetTile(int,int,int,int)\0int\0layer,x,y\0"
    "GetTile(int,int,int)\0GetLayers()\0layer\0"
    "GetLayerName(int)\0layer,name\0"
    "SetLayerName(int,QString)\0"
    "w,h,wrap,filltile,name\0"
    "AddLayer(int,int,bool,int,QString)\0"
    "w,h,wrap,filltile\0AddLayer(int,int,bool,int)\0"
    "w,h,wrap\0AddLayer(int,int,bool)\0w,h\0"
    "AddLayer(int,int)\0oldIndex,newIndex\0"
    "moveLayer(int,int)\0layer,w,h,wrap,filltile,name\0"
    "InsertLayerBefore(int,int,int,bool,int,QString)\0"
    "layer,w,h,wrap,filltile\0"
    "InsertLayerBefore(int,int,int,bool,int)\0"
    "layer,w,h,wrap\0InsertLayerBefore(int,int,int,bool)\0"
    "layer,w,h\0InsertLayerBefore(int,int,int)\0"
    "InsertLayerAfter(int,int,int,bool,int,QString)\0"
    "InsertLayerAfter(int,int,int,bool,int)\0"
    "InsertLayerAfter(int,int,int,bool)\0"
    "InsertLayerAfter(int,int,int)\0"
    "DeleteLayer(int)\0x,y,w,h\0"
    "SetViewport(int,int,int,int)\0layer,entity\0"
    "AddEntity(int,Entity*)\0"
    "AddStartEntity(int,Entity*)\0"
    "RemoveEntity(int,Entity*)\0"
    "RemoveStartEntity(int,Entity*)\0"
    "GetEntities(int)\0GetStartEntities(int)\0"
    "Reset()\0Clear()\0"
};

const QMetaObject Map::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Map,
      qt_meta_data_Map, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Map::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Map::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Map::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Map))
        return static_cast<void*>(const_cast< Map*>(this));
    return QObject::qt_metacast(_clname);
}

int Map::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: { bool _r = SetName((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 1: { QString _r = GetName();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 2: SetTile((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4]))); break;
        case 3: { int _r = GetTile((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 4: { int _r = GetLayers();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 5: { QString _r = GetLayerName((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 6: SetLayerName((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 7: { int _r = AddLayer((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4])),(*reinterpret_cast< QString(*)>(_a[5])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 8: { int _r = AddLayer((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 9: { int _r = AddLayer((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 10: { int _r = AddLayer((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 11: moveLayer((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 12: InsertLayerBefore((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< bool(*)>(_a[4])),(*reinterpret_cast< int(*)>(_a[5])),(*reinterpret_cast< QString(*)>(_a[6]))); break;
        case 13: InsertLayerBefore((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< bool(*)>(_a[4])),(*reinterpret_cast< int(*)>(_a[5]))); break;
        case 14: InsertLayerBefore((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< bool(*)>(_a[4]))); break;
        case 15: InsertLayerBefore((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 16: InsertLayerAfter((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< bool(*)>(_a[4])),(*reinterpret_cast< int(*)>(_a[5])),(*reinterpret_cast< QString(*)>(_a[6]))); break;
        case 17: InsertLayerAfter((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< bool(*)>(_a[4])),(*reinterpret_cast< int(*)>(_a[5]))); break;
        case 18: InsertLayerAfter((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< bool(*)>(_a[4]))); break;
        case 19: InsertLayerAfter((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 20: DeleteLayer((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 21: SetViewport((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4]))); break;
        case 22: AddEntity((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< Entity*(*)>(_a[2]))); break;
        case 23: AddStartEntity((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< Entity*(*)>(_a[2]))); break;
        case 24: RemoveEntity((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< Entity*(*)>(_a[2]))); break;
        case 25: RemoveStartEntity((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< Entity*(*)>(_a[2]))); break;
        case 26: { int _r = GetEntities((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 27: { int _r = GetStartEntities((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 28: Reset(); break;
        case 29: Clear(); break;
        default: ;
        }
        _id -= 30;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
