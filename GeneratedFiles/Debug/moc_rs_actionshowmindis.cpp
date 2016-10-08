/****************************************************************************
** Meta object code from reading C++ file 'rs_actionshowmindis.h'
**
** Created: Mon Sep 26 14:56:07 2016
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../actions/rs_actionshowmindis.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'rs_actionshowmindis.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_RS_ActionShowMinDis[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      35,   21,   20,   20, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_RS_ActionShowMinDis[] = {
    "RS_ActionShowMinDis\0\0start,end,dis\0"
    "s_sendMinDis(RS_Vector,RS_Vector,double)\0"
};

void RS_ActionShowMinDis::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        RS_ActionShowMinDis *_t = static_cast<RS_ActionShowMinDis *>(_o);
        switch (_id) {
        case 0: _t->s_sendMinDis((*reinterpret_cast< RS_Vector(*)>(_a[1])),(*reinterpret_cast< RS_Vector(*)>(_a[2])),(*reinterpret_cast< double(*)>(_a[3]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData RS_ActionShowMinDis::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject RS_ActionShowMinDis::staticMetaObject = {
    { &RS_PreviewActionInterface::staticMetaObject, qt_meta_stringdata_RS_ActionShowMinDis,
      qt_meta_data_RS_ActionShowMinDis, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &RS_ActionShowMinDis::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *RS_ActionShowMinDis::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *RS_ActionShowMinDis::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_RS_ActionShowMinDis))
        return static_cast<void*>(const_cast< RS_ActionShowMinDis*>(this));
    return RS_PreviewActionInterface::qt_metacast(_clname);
}

int RS_ActionShowMinDis::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = RS_PreviewActionInterface::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    }
    return _id;
}

// SIGNAL 0
void RS_ActionShowMinDis::s_sendMinDis(RS_Vector _t1, RS_Vector _t2, double _t3)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
