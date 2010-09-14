/****************************************************************************
** Meta object code from reading C++ file 'spritedialog.h'
**
** Created: Mon Sep 13 20:34:19 2010
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../qrpglib/spritedialog.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'spritedialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_AddStateDialog[] = {

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

static const char qt_meta_stringdata_AddStateDialog[] = {
    "AddStateDialog\0"
};

const QMetaObject AddStateDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_AddStateDialog,
      qt_meta_data_AddStateDialog, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &AddStateDialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *AddStateDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *AddStateDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_AddStateDialog))
        return static_cast<void*>(const_cast< AddStateDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int AddStateDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
static const uint qt_meta_data_AddSpriteDialog[] = {

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

static const char qt_meta_stringdata_AddSpriteDialog[] = {
    "AddSpriteDialog\0"
};

const QMetaObject AddSpriteDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_AddSpriteDialog,
      qt_meta_data_AddSpriteDialog, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &AddSpriteDialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *AddSpriteDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *AddSpriteDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_AddSpriteDialog))
        return static_cast<void*>(const_cast< AddSpriteDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int AddSpriteDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
static const uint qt_meta_data_SpriteDialog[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      25,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      14,   13,   13,   13, 0x0a,
      37,   13,   13,   13, 0x0a,
      60,   13,   13,   13, 0x0a,
      84,   13,   13,   13, 0x0a,
     102,   13,   13,   13, 0x0a,
     120,   13,   13,   13, 0x0a,
     137,   13,   13,   13, 0x0a,
     149,   13,   13,   13, 0x0a,
     161,   13,   13,   13, 0x0a,
     183,   13,   13,   13, 0x0a,
     209,   13,   13,   13, 0x0a,
     229,   13,   13,   13, 0x0a,
     264,   13,   13,   13, 0x0a,
     284,   13,   13,   13, 0x0a,
     300,   13,   13,   13, 0x0a,
     317,   13,   13,   13, 0x0a,
     332,   13,   13,   13, 0x0a,
     347,   13,   13,   13, 0x0a,
     378,   13,   13,   13, 0x0a,
     410,   13,   13,   13, 0x0a,
     421,   13,   13,   13, 0x0a,
     432,   13,   13,   13, 0x0a,
     443,   13,   13,   13, 0x0a,
     454,   13,   13,   13, 0x0a,
     461,   13,   13,   13, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_SpriteDialog[] = {
    "SpriteDialog\0\0updateSpritePulldown()\0"
    "spriteChanged(QString)\0tilesetChanged(QString)\0"
    "stateChanged(int)\0frameChanged(int)\0"
    "tileChanged(int)\0addSprite()\0delSprite()\0"
    "renameSprite(QString)\0setCurrentSprite(QString)\0"
    "setTileset(QString)\0"
    "durationChanged(QTableWidgetItem*)\0"
    "spriteNameChanged()\0updateWidgets()\0"
    "updateTilesets()\0updateStates()\0"
    "updateFrames()\0updateSpriteSliderCurrent(int)\0"
    "updateSpriteSliderDuration(int)\0"
    "addState()\0addFrame()\0delState()\0"
    "delFrame()\0show()\0disable(bool)\0"
};

const QMetaObject SpriteDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_SpriteDialog,
      qt_meta_data_SpriteDialog, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &SpriteDialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *SpriteDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *SpriteDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SpriteDialog))
        return static_cast<void*>(const_cast< SpriteDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int SpriteDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: updateSpritePulldown(); break;
        case 1: spriteChanged((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: tilesetChanged((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: stateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: frameChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: tileChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: addSprite(); break;
        case 7: delSprite(); break;
        case 8: renameSprite((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 9: setCurrentSprite((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 10: setTileset((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 11: durationChanged((*reinterpret_cast< QTableWidgetItem*(*)>(_a[1]))); break;
        case 12: spriteNameChanged(); break;
        case 13: updateWidgets(); break;
        case 14: updateTilesets(); break;
        case 15: updateStates(); break;
        case 16: updateFrames(); break;
        case 17: updateSpriteSliderCurrent((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 18: updateSpriteSliderDuration((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 19: addState(); break;
        case 20: addFrame(); break;
        case 21: delState(); break;
        case 22: delFrame(); break;
        case 23: show(); break;
        case 24: disable((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 25;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
