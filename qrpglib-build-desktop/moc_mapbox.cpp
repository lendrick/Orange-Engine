/****************************************************************************
** Meta object code from reading C++ file 'mapbox.h'
**
** Created: Mon Sep 13 13:41:31 2010
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../qrpglib/mapbox.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mapbox.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MapBox[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      34,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       7,       // signalCount

 // signals: signature, parameters, type, tag, flags
      10,    8,    7,    7, 0x05,
      29,    8,    7,    7, 0x05,
      48,    7,    7,    7, 0x05,
      64,    7,    7,    7, 0x05,
      80,    8,    7,    7, 0x05,
     103,    7,    7,    7, 0x05,
     124,  120,    7,    7, 0x05,

 // slots: signature, parameters, type, tag, flags
     150,    7,    7,    7, 0x0a,
     160,    7,    7,    7, 0x0a,
     170,    8,    7,    7, 0x0a,
     188,    7,  184,    7, 0x0a,
     195,    7,  184,    7, 0x0a,
     202,    7,    7,    7, 0x0a,
     216,  120,    7,    7, 0x0a,
     247,    7,    7,    7, 0x0a,
     264,    7,    7,    7, 0x0a,
     281,    7,  276,    7, 0x0a,
     295,    7,  290,    7, 0x0a,
     304,    7,    7,    7, 0x0a,
     319,    7,    7,    7, 0x0a,
     359,    7,  334,    7, 0x0a,
     373,    7,    7,    7, 0x0a,
     400,    7,  392,    7, 0x0a,
     412,    7,    7,    7, 0x0a,
     450,    7,    7,    7, 0x0a,
     470,    7,    7,    7, 0x0a,
     494,  490,  392,    7, 0x0a,
     527,  490,  512,    7, 0x0a,
     547,    7,    7,    7, 0x0a,
     561,    7,    7,    7, 0x0a,
     577,    7,    7,    7, 0x0a,
     593,    7,    7,    7, 0x0a,
     613,  608,    7,    7, 0x0a,
     626,    7,  184,    7, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_MapBox[] = {
    "MapBox\0\0,\0SetXRange(int,int)\0"
    "SetYRange(int,int)\0SetXScroll(int)\0"
    "SetYScroll(int)\0SetLayerRange(int,int)\0"
    "modeChanged(int)\0,,,\0mousePos(int,int,int,int)\0"
    "SetX(int)\0SetY(int)\0Move(int,int)\0int\0"
    "GetX()\0GetY()\0SetLayer(int)\0"
    "AddLayer(int,int,bool,QString)\0"
    "DeleteLayer(int)\0SetMap(int)\0Map*\0"
    "GetMap()\0bool\0HasMap()\0LoadMap(char*)\0"
    "SaveMap(char*)\0LayerView::LayerViewMode\0"
    "getDrawMode()\0setCamera(Entity*)\0"
    "Entity*\0getCamera()\0"
    "setDrawMode(LayerView::LayerViewMode)\0"
    "setCurrentTile(int)\0addWidget(QWidget*)\0"
    "x,y\0entityAt(int,int)\0QList<Entity*>\0"
    "entitiesAt(int,int)\0setEditMode()\0"
    "setEntityMode()\0setSelectMode()\0"
    "setBrushMode()\0mode\0setMode(int)\0"
    "getMode()\0"
};

const QMetaObject MapBox::staticMetaObject = {
    { &QGraphicsView::staticMetaObject, qt_meta_stringdata_MapBox,
      qt_meta_data_MapBox, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MapBox::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MapBox::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MapBox::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MapBox))
        return static_cast<void*>(const_cast< MapBox*>(this));
    return QGraphicsView::qt_metacast(_clname);
}

int MapBox::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGraphicsView::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: SetXRange((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 1: SetYRange((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 2: SetXScroll((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: SetYScroll((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: SetLayerRange((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 5: modeChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: mousePos((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4]))); break;
        case 7: SetX((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: SetY((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: Move((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 10: { int _r = GetX();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 11: { int _r = GetY();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 12: SetLayer((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 13: AddLayer((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4]))); break;
        case 14: DeleteLayer((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 15: SetMap((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 16: { Map* _r = GetMap();
            if (_a[0]) *reinterpret_cast< Map**>(_a[0]) = _r; }  break;
        case 17: { bool _r = HasMap();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 18: LoadMap((*reinterpret_cast< char*(*)>(_a[1]))); break;
        case 19: SaveMap((*reinterpret_cast< char*(*)>(_a[1]))); break;
        case 20: { LayerView::LayerViewMode _r = getDrawMode();
            if (_a[0]) *reinterpret_cast< LayerView::LayerViewMode*>(_a[0]) = _r; }  break;
        case 21: setCamera((*reinterpret_cast< Entity*(*)>(_a[1]))); break;
        case 22: { Entity* _r = getCamera();
            if (_a[0]) *reinterpret_cast< Entity**>(_a[0]) = _r; }  break;
        case 23: setDrawMode((*reinterpret_cast< LayerView::LayerViewMode(*)>(_a[1]))); break;
        case 24: setCurrentTile((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 25: addWidget((*reinterpret_cast< QWidget*(*)>(_a[1]))); break;
        case 26: { Entity* _r = entityAt((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< Entity**>(_a[0]) = _r; }  break;
        case 27: { QList<Entity*> _r = entitiesAt((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QList<Entity*>*>(_a[0]) = _r; }  break;
        case 28: setEditMode(); break;
        case 29: setEntityMode(); break;
        case 30: setSelectMode(); break;
        case 31: setBrushMode(); break;
        case 32: setMode((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 33: { int _r = getMode();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        default: ;
        }
        _id -= 34;
    }
    return _id;
}

// SIGNAL 0
void MapBox::SetXRange(int _t1, int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void MapBox::SetYRange(int _t1, int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void MapBox::SetXScroll(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void MapBox::SetYScroll(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void MapBox::SetLayerRange(int _t1, int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void MapBox::modeChanged(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void MapBox::mousePos(int _t1, int _t2, int _t3, int _t4)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}
static const uint qt_meta_data_MapScene[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      10,    9,    9,    9, 0x05,

 // slots: signature, parameters, type, tag, flags
      36,    9,    9,    9, 0x0a,
      48,    9,    9,    9, 0x0a,
      63,    9,    9,    9, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_MapScene[] = {
    "MapScene\0\0ShowEntityDialog(Entity*)\0"
    "newEntity()\0deleteEntity()\0editEntity()\0"
};

const QMetaObject MapScene::staticMetaObject = {
    { &QGraphicsScene::staticMetaObject, qt_meta_stringdata_MapScene,
      qt_meta_data_MapScene, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MapScene::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MapScene::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MapScene::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MapScene))
        return static_cast<void*>(const_cast< MapScene*>(this));
    return QGraphicsScene::qt_metacast(_clname);
}

int MapScene::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGraphicsScene::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: ShowEntityDialog((*reinterpret_cast< Entity*(*)>(_a[1]))); break;
        case 1: newEntity(); break;
        case 2: deleteEntity(); break;
        case 3: editEntity(); break;
        default: ;
        }
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void MapScene::ShowEntityDialog(Entity * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
