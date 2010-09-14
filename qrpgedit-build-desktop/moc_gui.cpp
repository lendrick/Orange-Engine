/****************************************************************************
** Meta object code from reading C++ file 'gui.h'
**
** Created: Mon Sep 13 20:44:28 2010
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../qrpgedit/gui.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'gui.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MainWindow[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      28,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x05,
      24,   11,   11,   11, 0x05,
      38,   11,   11,   11, 0x05,
      53,   11,   11,   11, 0x05,

 // slots: signature, parameters, type, tag, flags
      78,   11,   11,   11, 0x0a,
     102,   11,   11,   11, 0x0a,
     128,   11,   11,   11, 0x0a,
     145,   11,   11,   11, 0x0a,
     164,   11,   11,   11, 0x0a,
     174,   11,   11,   11, 0x0a,
     187,   11,   11,   11, 0x0a,
     201,   11,   11,   11, 0x0a,
     222,   11,   11,   11, 0x0a,
     236,   11,   11,   11, 0x0a,
     245,   11,   11,   11, 0x0a,
     255,   11,   11,   11, 0x0a,
     265,   11,   11,   11, 0x0a,
     277,   11,   11,   11, 0x0a,
     289,   11,   11,   11, 0x0a,
     317,   11,   11,   11, 0x0a,
     349,   11,   11,   11, 0x0a,
     379,   11,   11,   11, 0x0a,
     410,  406,   11,   11, 0x0a,
     442,   11,   11,   11, 0x0a,
     470,   11,   11,   11, 0x0a,
     477,   11,   11,   11, 0x0a,
     498,   11,   11,   11, 0x0a,
     523,   11,   11,   11, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_MainWindow[] = {
    "MainWindow\0\0SetMap(int)\0SetTiles(int)\0"
    "updateLayers()\0UpdateMapStatus(QString)\0"
    "ShowNewLayerDialog(int)\0"
    "ShowEntityDialog(Entity*)\0deleteLayer(int)\0"
    "ResourceSelected()\0AboutQt()\0NewProject()\0"
    "LoadProject()\0LoadProject(QString)\0"
    "SaveProject()\0NewMap()\0LoadMap()\0"
    "SaveMap()\0NewBitmap()\0NewSprite()\0"
    "SetMapButtonsDisabled(bool)\0"
    "SetTilesetButtonsDisabled(bool)\0"
    "SetLayerButtonsDisabled(bool)\0"
    "SetLayerButtonsForMap(int)\0,,,\0"
    "UpdateMousePos(int,int,int,int)\0"
    "UpdateProjectTitle(QString)\0play()\0"
    "setViewTilePos(bool)\0setViewEntityNames(bool)\0"
    "setViewGrid(bool)\0"
};

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow,
      qt_meta_data_MainWindow, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MainWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: SetMap((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: SetTiles((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: updateLayers(); break;
        case 3: UpdateMapStatus((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: ShowNewLayerDialog((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: ShowEntityDialog((*reinterpret_cast< Entity*(*)>(_a[1]))); break;
        case 6: deleteLayer((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: ResourceSelected(); break;
        case 8: AboutQt(); break;
        case 9: NewProject(); break;
        case 10: LoadProject(); break;
        case 11: LoadProject((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 12: SaveProject(); break;
        case 13: NewMap(); break;
        case 14: LoadMap(); break;
        case 15: SaveMap(); break;
        case 16: NewBitmap(); break;
        case 17: NewSprite(); break;
        case 18: SetMapButtonsDisabled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 19: SetTilesetButtonsDisabled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 20: SetLayerButtonsDisabled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 21: SetLayerButtonsForMap((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 22: UpdateMousePos((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4]))); break;
        case 23: UpdateProjectTitle((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 24: play(); break;
        case 25: setViewTilePos((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 26: setViewEntityNames((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 27: setViewGrid((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 28;
    }
    return _id;
}

// SIGNAL 0
void MainWindow::SetMap(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void MainWindow::SetTiles(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void MainWindow::updateLayers()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}

// SIGNAL 3
void MainWindow::UpdateMapStatus(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_END_MOC_NAMESPACE
