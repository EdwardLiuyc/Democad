/****************************************************************************
** Meta object code from reading C++ file 'qg_showposofTP.h'
**
** Created: Mon Sep 26 14:56:09 2016
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../ui/forms/qg_showposofTP.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qg_showposofTP.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QG_ShowPosOfTP[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      26,   16,   15,   15, 0x09,
      97,   60,   15,   15, 0x09,
     175,  161,   15,   15, 0x09,
     208,   15,   15,   15, 0x09,
     226,   15,   15,   15, 0x09,
     243,   15,   15,   15, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_QG_ShowPosOfTP[] = {
    "QG_ShowPosOfTP\0\0start,end\0"
    "showLineInfo(RS_Vector,RS_Vector)\0"
    "start,end,center,angle,length,radius\0"
    "showArcInfo(RS_Vector,RS_Vector,RS_Vector,double,double,double)\0"
    "center,radius\0showCircleInfo(RS_Vector,double)\0"
    "showLineTipInfo()\0showArcTipInfo()\0"
    "showCircleTipInfo()\0"
};

void QG_ShowPosOfTP::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QG_ShowPosOfTP *_t = static_cast<QG_ShowPosOfTP *>(_o);
        switch (_id) {
        case 0: _t->showLineInfo((*reinterpret_cast< RS_Vector(*)>(_a[1])),(*reinterpret_cast< RS_Vector(*)>(_a[2]))); break;
        case 1: _t->showArcInfo((*reinterpret_cast< RS_Vector(*)>(_a[1])),(*reinterpret_cast< RS_Vector(*)>(_a[2])),(*reinterpret_cast< RS_Vector(*)>(_a[3])),(*reinterpret_cast< double(*)>(_a[4])),(*reinterpret_cast< double(*)>(_a[5])),(*reinterpret_cast< double(*)>(_a[6]))); break;
        case 2: _t->showCircleInfo((*reinterpret_cast< RS_Vector(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2]))); break;
        case 3: _t->showLineTipInfo(); break;
        case 4: _t->showArcTipInfo(); break;
        case 5: _t->showCircleTipInfo(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData QG_ShowPosOfTP::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QG_ShowPosOfTP::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_QG_ShowPosOfTP,
      qt_meta_data_QG_ShowPosOfTP, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QG_ShowPosOfTP::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QG_ShowPosOfTP::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QG_ShowPosOfTP::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QG_ShowPosOfTP))
        return static_cast<void*>(const_cast< QG_ShowPosOfTP*>(this));
    if (!strcmp(_clname, "QG_BaseOptions"))
        return static_cast< QG_BaseOptions*>(const_cast< QG_ShowPosOfTP*>(this));
    return QWidget::qt_metacast(_clname);
}

int QG_ShowPosOfTP::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
