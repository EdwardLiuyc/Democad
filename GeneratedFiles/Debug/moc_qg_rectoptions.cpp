/****************************************************************************
** Meta object code from reading C++ file 'qg_rectoptions.h'
**
** Created: Mon Sep 26 14:56:10 2016
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../ui/forms/qg_rectoptions.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qg_rectoptions.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QG_RectOptions[] = {

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
      16,   15,   15,   15, 0x0a,
      27,   15,   15,   15, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_QG_RectOptions[] = {
    "QG_RectOptions\0\0slotNext()\0slotOk()\0"
};

void QG_RectOptions::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QG_RectOptions *_t = static_cast<QG_RectOptions *>(_o);
        switch (_id) {
        case 0: _t->slotNext(); break;
        case 1: _t->slotOk(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData QG_RectOptions::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QG_RectOptions::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_QG_RectOptions,
      qt_meta_data_QG_RectOptions, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QG_RectOptions::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QG_RectOptions::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QG_RectOptions::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QG_RectOptions))
        return static_cast<void*>(const_cast< QG_RectOptions*>(this));
    if (!strcmp(_clname, "QG_BaseOptions"))
        return static_cast< QG_BaseOptions*>(const_cast< QG_RectOptions*>(this));
    return QWidget::qt_metacast(_clname);
}

int QG_RectOptions::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
