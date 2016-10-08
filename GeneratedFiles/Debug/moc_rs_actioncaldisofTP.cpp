/****************************************************************************
** Meta object code from reading C++ file 'rs_actioncaldisofTP.h'
**
** Created: Mon Sep 26 14:56:08 2016
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../actions/rs_actioncaldisofTP.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'rs_actioncaldisofTP.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_RS_ActionCalDisOfTp[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      27,   21,   20,   20, 0x05,
      57,   53,   20,   20, 0x05,

 // slots: signature, parameters, type, tag, flags
      87,   81,   20,   20, 0x0a,
     107,  105,   20,   20, 0x0a,
     124,  105,   20,   20, 0x0a,
     140,  105,   20,   20, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_RS_ActionCalDisOfTp[] = {
    "RS_ActionCalDisOfTp\0\0start\0"
    "s_sendstartpos(RS_Vector)\0end\0"
    "s_sendendpos(RS_Vector)\0mpost\0"
    "OnCommit(MyPoint)\0f\0OnRight(QString)\0"
    "OnLeft(QString)\0OnEnter(QString)\0"
};

void RS_ActionCalDisOfTp::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        RS_ActionCalDisOfTp *_t = static_cast<RS_ActionCalDisOfTp *>(_o);
        switch (_id) {
        case 0: _t->s_sendstartpos((*reinterpret_cast< RS_Vector(*)>(_a[1]))); break;
        case 1: _t->s_sendendpos((*reinterpret_cast< RS_Vector(*)>(_a[1]))); break;
        case 2: _t->OnCommit((*reinterpret_cast< MyPoint(*)>(_a[1]))); break;
        case 3: _t->OnRight((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: _t->OnLeft((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 5: _t->OnEnter((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData RS_ActionCalDisOfTp::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject RS_ActionCalDisOfTp::staticMetaObject = {
    { &RS_PreviewActionInterface::staticMetaObject, qt_meta_stringdata_RS_ActionCalDisOfTp,
      qt_meta_data_RS_ActionCalDisOfTp, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &RS_ActionCalDisOfTp::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *RS_ActionCalDisOfTp::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *RS_ActionCalDisOfTp::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_RS_ActionCalDisOfTp))
        return static_cast<void*>(const_cast< RS_ActionCalDisOfTp*>(this));
    return RS_PreviewActionInterface::qt_metacast(_clname);
}

int RS_ActionCalDisOfTp::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = RS_PreviewActionInterface::qt_metacall(_c, _id, _a);
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
void RS_ActionCalDisOfTp::s_sendstartpos(RS_Vector _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void RS_ActionCalDisOfTp::s_sendendpos(RS_Vector _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
