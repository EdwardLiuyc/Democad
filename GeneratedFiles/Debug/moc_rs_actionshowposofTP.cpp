/****************************************************************************
** Meta object code from reading C++ file 'rs_actionshowposofTP.h'
**
** Created: Mon Sep 26 14:56:07 2016
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../actions/rs_actionshowposofTP.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'rs_actionshowposofTP.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_RS_ActionShowPosOfTp[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: signature, parameters, type, tag, flags
      32,   22,   21,   21, 0x05,
     105,   68,   21,   21, 0x05,
     185,  171,   21,   21, 0x05,
     220,   21,   21,   21, 0x05,
     240,   21,   21,   21, 0x05,
     259,   21,   21,   21, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_RS_ActionShowPosOfTp[] = {
    "RS_ActionShowPosOfTp\0\0start,end\0"
    "s_sendLineInfo(RS_Vector,RS_Vector)\0"
    "start,end,center,angle,length,radius\0"
    "s_sendArcInfo(RS_Vector,RS_Vector,RS_Vector,double,double,double)\0"
    "center,radius\0s_sendCircleInfo(RS_Vector,double)\0"
    "s_sendLineTipInfo()\0s_sendArcTipInfo()\0"
    "s_sendCircleTipInfo()\0"
};

void RS_ActionShowPosOfTp::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        RS_ActionShowPosOfTp *_t = static_cast<RS_ActionShowPosOfTp *>(_o);
        switch (_id) {
        case 0: _t->s_sendLineInfo((*reinterpret_cast< RS_Vector(*)>(_a[1])),(*reinterpret_cast< RS_Vector(*)>(_a[2]))); break;
        case 1: _t->s_sendArcInfo((*reinterpret_cast< RS_Vector(*)>(_a[1])),(*reinterpret_cast< RS_Vector(*)>(_a[2])),(*reinterpret_cast< RS_Vector(*)>(_a[3])),(*reinterpret_cast< double(*)>(_a[4])),(*reinterpret_cast< double(*)>(_a[5])),(*reinterpret_cast< double(*)>(_a[6]))); break;
        case 2: _t->s_sendCircleInfo((*reinterpret_cast< RS_Vector(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2]))); break;
        case 3: _t->s_sendLineTipInfo(); break;
        case 4: _t->s_sendArcTipInfo(); break;
        case 5: _t->s_sendCircleTipInfo(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData RS_ActionShowPosOfTp::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject RS_ActionShowPosOfTp::staticMetaObject = {
    { &RS_PreviewActionInterface::staticMetaObject, qt_meta_stringdata_RS_ActionShowPosOfTp,
      qt_meta_data_RS_ActionShowPosOfTp, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &RS_ActionShowPosOfTp::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *RS_ActionShowPosOfTp::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *RS_ActionShowPosOfTp::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_RS_ActionShowPosOfTp))
        return static_cast<void*>(const_cast< RS_ActionShowPosOfTp*>(this));
    return RS_PreviewActionInterface::qt_metacast(_clname);
}

int RS_ActionShowPosOfTp::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void RS_ActionShowPosOfTp::s_sendLineInfo(RS_Vector _t1, RS_Vector _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void RS_ActionShowPosOfTp::s_sendArcInfo(RS_Vector _t1, RS_Vector _t2, RS_Vector _t3, double _t4, double _t5, double _t6)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)), const_cast<void*>(reinterpret_cast<const void*>(&_t5)), const_cast<void*>(reinterpret_cast<const void*>(&_t6)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void RS_ActionShowPosOfTp::s_sendCircleInfo(RS_Vector _t1, double _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void RS_ActionShowPosOfTp::s_sendLineTipInfo()
{
    QMetaObject::activate(this, &staticMetaObject, 3, 0);
}

// SIGNAL 4
void RS_ActionShowPosOfTp::s_sendArcTipInfo()
{
    QMetaObject::activate(this, &staticMetaObject, 4, 0);
}

// SIGNAL 5
void RS_ActionShowPosOfTp::s_sendCircleTipInfo()
{
    QMetaObject::activate(this, &staticMetaObject, 5, 0);
}
QT_END_MOC_NAMESPACE
