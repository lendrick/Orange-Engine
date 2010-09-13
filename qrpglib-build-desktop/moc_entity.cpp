/****************************************************************************
** Meta object code from reading C++ file 'entity.h'
**
** Created: Mon Sep 13 14:58:26 2010
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../qrpglib/entity.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'entity.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Entity[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      44,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      16,    7,    8,    7, 0x0a,
      28,    7,   24,    7, 0x0a,
      39,    7,   24,    7, 0x0a,
      55,    7,   47,    7, 0x0a,
      70,    7,    7,    7, 0x0a,
      92,    7,   84,    7, 0x0a,
     109,    7,  104,    7, 0x0a,
     118,    7,    7,    7, 0x0a,
     139,  137,    7,    7, 0x0a,
     165,    7,  158,    7, 0x0a,
     172,    7,  158,    7, 0x0a,
     179,    7,    7,    7, 0x0a,
     192,    7,    7,    7, 0x0a,
     207,  205,    7,    7, 0x0a,
     227,  205,    7,    7, 0x0a,
     249,  205,    7,    7, 0x0a,
     272,    7,    7,    7, 0x0a,
     289,    7,   47,    7, 0x0a,
     299,    7,    7,    7, 0x0a,
     317,  313,    7,    7, 0x0a,
     353,  313,    7,    7, 0x0a,
     405,  313,    7,    7, 0x0a,
     439,  313,    7,    7, 0x0a,
     489,    7,    7,    7, 0x0a,
     509,    7,  504,    7, 0x0a,
     550,  519,    7,    7, 0x0a,
     622,  594,    7,    7, 0x2a,
     687,  662,    7,    7, 0x2a,
     745,  723,    7,    7, 0x2a,
     796,  777,    7,    7, 0x2a,
     824,  205,    7,    7, 0x2a,
     847,    7,    7,    7, 0x0a,
     862,    7,   24,    7, 0x0a,
     879,    7,   47,    7, 0x0a,
     894,    7,   24,    7, 0x0a,
     918,    7,  504,    7, 0x0a,
     946,  941,    7,    7, 0x0a,
     992,  941,    7,    7, 0x0a,
    1054,  137,    7,    7, 0x0a,
    1067,    7,    7,    7, 0x0a,
    1085,    7,    7,    7, 0x0a,
    1093,    7,    7,    7, 0x0a,
    1101,    7,    7,    7, 0x0a,
    1112,    7,   24,    7, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_Entity[] = {
    "Entity\0\0Entity*\0clone()\0int\0getState()\0"
    "getId()\0QString\0getStateName()\0"
    "setState(int)\0Sprite*\0getSprite()\0"
    "Map*\0getMap()\0setSprite(Sprite*)\0s\0"
    "setSprite(QString)\0double\0getX()\0"
    "getY()\0setX(double)\0setY(double)\0,\0"
    "move(double,double)\0setPos(double,double)\0"
    "movePos(double,double)\0setName(QString)\0"
    "getName()\0addToMap(int)\0,,,\0"
    "getBoundingBox(int&,int&,int&,int&)\0"
    "getRealBoundingBox(double&,double&,double&,double&)\0"
    "getSpriteBox(int&,int&,int&,int&)\0"
    "getRealSpriteBox(double&,double&,double&,double&)\0"
    "setSolid(bool)\0bool\0isSolid()\0"
    ",,useDefaultBounds,x1,y1,x2,y2\0"
    "addScript(int,QString,bool,int,int,int,int)\0"
    ",,useDefaultBounds,x1,y1,x2\0"
    "addScript(int,QString,bool,int,int,int)\0"
    ",,useDefaultBounds,x1,y1\0"
    "addScript(int,QString,bool,int,int)\0"
    ",,useDefaultBounds,x1\0"
    "addScript(int,QString,bool,int)\0"
    ",,useDefaultBounds\0addScript(int,QString,bool)\0"
    "addScript(int,QString)\0clearScripts()\0"
    "getScriptCount()\0getScript(int)\0"
    "getScriptCondition(int)\0usesDefaultBounds(int)\0"
    ",,,,\0getScriptBoundingBox(int,int&,int&,int&,int&)\0"
    "getRealScriptBoundingBox(int,double&,double&,double&,double&)\0"
    "say(QString)\0getScriptObject()\0start()\0"
    "touch()\0activate()\0getLayer()\0"
};

const QMetaObject Entity::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Entity,
      qt_meta_data_Entity, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Entity::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Entity::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Entity::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Entity))
        return static_cast<void*>(const_cast< Entity*>(this));
    if (!strcmp(_clname, "QScriptable"))
        return static_cast< QScriptable*>(const_cast< Entity*>(this));
    return QObject::qt_metacast(_clname);
}

int Entity::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: { Entity* _r = clone();
            if (_a[0]) *reinterpret_cast< Entity**>(_a[0]) = _r; }  break;
        case 1: { int _r = getState();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 2: { int _r = getId();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 3: { QString _r = getStateName();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 4: setState((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: { Sprite* _r = getSprite();
            if (_a[0]) *reinterpret_cast< Sprite**>(_a[0]) = _r; }  break;
        case 6: { Map* _r = getMap();
            if (_a[0]) *reinterpret_cast< Map**>(_a[0]) = _r; }  break;
        case 7: setSprite((*reinterpret_cast< Sprite*(*)>(_a[1]))); break;
        case 8: setSprite((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 9: { double _r = getX();
            if (_a[0]) *reinterpret_cast< double*>(_a[0]) = _r; }  break;
        case 10: { double _r = getY();
            if (_a[0]) *reinterpret_cast< double*>(_a[0]) = _r; }  break;
        case 11: setX((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 12: setY((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 13: move((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2]))); break;
        case 14: setPos((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2]))); break;
        case 15: movePos((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2]))); break;
        case 16: setName((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 17: { QString _r = getName();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 18: addToMap((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 19: getBoundingBox((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4]))); break;
        case 20: getRealBoundingBox((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2])),(*reinterpret_cast< double(*)>(_a[3])),(*reinterpret_cast< double(*)>(_a[4]))); break;
        case 21: getSpriteBox((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4]))); break;
        case 22: getRealSpriteBox((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2])),(*reinterpret_cast< double(*)>(_a[3])),(*reinterpret_cast< double(*)>(_a[4]))); break;
        case 23: setSolid((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 24: { bool _r = isSolid();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 25: addScript((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4])),(*reinterpret_cast< int(*)>(_a[5])),(*reinterpret_cast< int(*)>(_a[6])),(*reinterpret_cast< int(*)>(_a[7]))); break;
        case 26: addScript((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4])),(*reinterpret_cast< int(*)>(_a[5])),(*reinterpret_cast< int(*)>(_a[6]))); break;
        case 27: addScript((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4])),(*reinterpret_cast< int(*)>(_a[5]))); break;
        case 28: addScript((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4]))); break;
        case 29: addScript((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3]))); break;
        case 30: addScript((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 31: clearScripts(); break;
        case 32: { int _r = getScriptCount();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 33: { QString _r = getScript((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 34: { int _r = getScriptCondition((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 35: { bool _r = usesDefaultBounds((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 36: getScriptBoundingBox((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4])),(*reinterpret_cast< int(*)>(_a[5]))); break;
        case 37: getRealScriptBoundingBox((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2])),(*reinterpret_cast< double(*)>(_a[3])),(*reinterpret_cast< double(*)>(_a[4])),(*reinterpret_cast< double(*)>(_a[5]))); break;
        case 38: say((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 39: getScriptObject(); break;
        case 40: start(); break;
        case 41: touch(); break;
        case 42: activate(); break;
        case 43: { int _r = getLayer();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        default: ;
        }
        _id -= 44;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
