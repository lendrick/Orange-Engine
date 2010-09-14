/****************************************************************************
** Meta object code from reading C++ file 'layerpanel.h'
**
** Created: Mon Sep 13 20:37:12 2010
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../qrpglib/layerpanel.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'layerpanel.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_LayerTable[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      14,   12,   11,   11, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_LayerTable[] = {
    "LayerTable\0\0,\0rowDragged(int,int)\0"
};

const QMetaObject LayerTable::staticMetaObject = {
    { &QTableWidget::staticMetaObject, qt_meta_stringdata_LayerTable,
      qt_meta_data_LayerTable, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &LayerTable::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *LayerTable::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *LayerTable::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_LayerTable))
        return static_cast<void*>(const_cast< LayerTable*>(this));
    return QTableWidget::qt_metacast(_clname);
}

int LayerTable::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QTableWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: rowDragged((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        default: ;
        }
        _id -= 1;
    }
    return _id;
}

// SIGNAL 0
void LayerTable::rowDragged(int _t1, int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
static const uint qt_meta_data_LayerPanel[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x05,
      26,   11,   11,   11, 0x05,
      40,   11,   11,   11, 0x05,
      57,   11,   11,   11, 0x05,

 // slots: signature, parameters, type, tag, flags
      95,   11,   11,   11, 0x0a,
     112,   11,   11,   11, 0x0a,
     129,   11,   11,   11, 0x0a,
     144,  142,   11,   11, 0x0a,
     165,  142,   11,   11, 0x0a,
     186,   11,   11,   11, 0x0a,
     204,   11,   11,   11, 0x0a,
     225,  142,   11,   11, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_LayerPanel[] = {
    "LayerPanel\0\0addLayer(int)\0delLayer(int)\0"
    "selectLayer(int)\0setDrawMode(LayerView::LayerViewMode)\0"
    "addLayerButton()\0delLayerButton()\0"
    "updateData()\0,\0renameLayer(int,int)\0"
    "cellClicked(int,int)\0setDisabled(bool)\0"
    "viewModeChanged(int)\0layerMoved(int,int)\0"
};

const QMetaObject LayerPanel::staticMetaObject = {
    { &QDockWidget::staticMetaObject, qt_meta_stringdata_LayerPanel,
      qt_meta_data_LayerPanel, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &LayerPanel::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *LayerPanel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *LayerPanel::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_LayerPanel))
        return static_cast<void*>(const_cast< LayerPanel*>(this));
    return QDockWidget::qt_metacast(_clname);
}

int LayerPanel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDockWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: addLayer((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: delLayer((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: selectLayer((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: setDrawMode((*reinterpret_cast< LayerView::LayerViewMode(*)>(_a[1]))); break;
        case 4: addLayerButton(); break;
        case 5: delLayerButton(); break;
        case 6: updateData(); break;
        case 7: renameLayer((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 8: cellClicked((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 9: setDisabled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 10: viewModeChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 11: layerMoved((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        default: ;
        }
        _id -= 12;
    }
    return _id;
}

// SIGNAL 0
void LayerPanel::addLayer(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void LayerPanel::delLayer(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void LayerPanel::selectLayer(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void LayerPanel::setDrawMode(LayerView::LayerViewMode _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_END_MOC_NAMESPACE
