/****************************************************************************
** Meta object code from reading C++ file 'qg_showmindis.h'
**
** Created: Mon Sep 26 14:56:09 2016
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../ui/forms/qg_showmindis.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qg_showmindis.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QG_ShowMinDistance[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      34,   20,   19,   19, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_QG_ShowMinDistance[] = {
    "QG_ShowMinDistance\0\0start,end,dis\0"
    "slotshowMindis(RS_Vector,RS_Vector,double)\0"
};

void QG_ShowMinDistance::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QG_ShowMinDistance *_t = static_cast<QG_ShowMinDistance *>(_o);
        switch (_id) {
        case 0: _t->slotshowMindis((*reinterpret_cast< RS_Vector(*)>(_a[1])),(*reinterpret_cast< RS_Vector(*)>(_a[2])),(*reinterpret_cast< double(*)>(_a[3]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData QG_ShowMinDistance::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QG_ShowMinDistance::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_QG_ShowMinDistance,
      qt_meta_data_QG_ShowMinDistance, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QG_ShowMinDistance::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QG_ShowMinDistance::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QG_ShowMinDistance::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QG_ShowMinDistance))
        return static_cast<void*>(const_cast< QG_ShowMinDistance*>(this));
    if (!strcmp(_clname, "QG_BaseOptions"))
        return static_cast< QG_BaseOptions*>(const_cast< QG_ShowMinDistance*>(this));
    return QWidget::qt_metacast(_clname);
}

int QG_ShowMinDistance::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
