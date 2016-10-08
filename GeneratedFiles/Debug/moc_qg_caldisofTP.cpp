/****************************************************************************
** Meta object code from reading C++ file 'qg_caldisofTP.h'
**
** Created: Mon Sep 26 14:56:10 2016
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../ui/forms/qg_caldisofTP.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qg_caldisofTP.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QG_CalDisOfTP[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      21,   15,   14,   14, 0x09,
      49,   45,   14,   14, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_QG_CalDisOfTP[] = {
    "QG_CalDisOfTP\0\0start\0showStartPos(RS_Vector)\0"
    "end\0showEndPos(RS_Vector)\0"
};

void QG_CalDisOfTP::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QG_CalDisOfTP *_t = static_cast<QG_CalDisOfTP *>(_o);
        switch (_id) {
        case 0: _t->showStartPos((*reinterpret_cast< RS_Vector(*)>(_a[1]))); break;
        case 1: _t->showEndPos((*reinterpret_cast< RS_Vector(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData QG_CalDisOfTP::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QG_CalDisOfTP::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_QG_CalDisOfTP,
      qt_meta_data_QG_CalDisOfTP, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QG_CalDisOfTP::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QG_CalDisOfTP::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QG_CalDisOfTP::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QG_CalDisOfTP))
        return static_cast<void*>(const_cast< QG_CalDisOfTP*>(this));
    if (!strcmp(_clname, "QG_BaseOptions"))
        return static_cast< QG_BaseOptions*>(const_cast< QG_CalDisOfTP*>(this));
    return QWidget::qt_metacast(_clname);
}

int QG_CalDisOfTP::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
