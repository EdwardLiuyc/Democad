/****************************************************************************
** Meta object code from reading C++ file 'RS_CustomBtn.h'
**
** Created: Mon Sep 26 14:56:08 2016
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../RS_CustomBtn.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'RS_CustomBtn.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_RS_CustomBtn[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: signature, parameters, type, tag, flags
      14,   13,   13,   13, 0x05,
      32,   13,   13,   13, 0x05,
      51,   13,   13,   13, 0x05,
      79,   77,   13,   13, 0x05,

 // slots: signature, parameters, type, tag, flags
     109,   13,   13,   13, 0x09,
     121,   13,   13,   13, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_RS_CustomBtn[] = {
    "RS_CustomBtn\0\0focusIn(QWidget*)\0"
    "focusOut(QWidget*)\0clickedWithThis(QWidget*)\0"
    ",\0toggledClicked(QWidget*,bool)\0"
    "onClicked()\0onToggle(bool)\0"
};

void RS_CustomBtn::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        RS_CustomBtn *_t = static_cast<RS_CustomBtn *>(_o);
        switch (_id) {
        case 0: _t->focusIn((*reinterpret_cast< QWidget*(*)>(_a[1]))); break;
        case 1: _t->focusOut((*reinterpret_cast< QWidget*(*)>(_a[1]))); break;
        case 2: _t->clickedWithThis((*reinterpret_cast< QWidget*(*)>(_a[1]))); break;
        case 3: _t->toggledClicked((*reinterpret_cast< QWidget*(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 4: _t->onClicked(); break;
        case 5: _t->onToggle((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData RS_CustomBtn::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject RS_CustomBtn::staticMetaObject = {
    { &QPushButton::staticMetaObject, qt_meta_stringdata_RS_CustomBtn,
      qt_meta_data_RS_CustomBtn, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &RS_CustomBtn::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *RS_CustomBtn::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *RS_CustomBtn::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_RS_CustomBtn))
        return static_cast<void*>(const_cast< RS_CustomBtn*>(this));
    return QPushButton::qt_metacast(_clname);
}

int RS_CustomBtn::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QPushButton::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void RS_CustomBtn::focusIn(QWidget * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void RS_CustomBtn::focusOut(QWidget * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void RS_CustomBtn::clickedWithThis(QWidget * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void RS_CustomBtn::toggledClicked(QWidget * _t1, bool _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_END_MOC_NAMESPACE
