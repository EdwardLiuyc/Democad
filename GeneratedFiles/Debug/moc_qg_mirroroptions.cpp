/****************************************************************************
** Meta object code from reading C++ file 'qg_mirroroptions.h'
**
** Created: Mon Sep 26 14:56:10 2016
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../ui/forms/qg_mirroroptions.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qg_mirroroptions.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QG_MirrorOptions[] = {

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
      18,   17,   17,   17, 0x0a,
      33,   17,   17,   17, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_QG_MirrorOptions[] = {
    "QG_MirrorOptions\0\0changeSelect()\0"
    "mirrorFixed()\0"
};

void QG_MirrorOptions::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QG_MirrorOptions *_t = static_cast<QG_MirrorOptions *>(_o);
        switch (_id) {
        case 0: _t->changeSelect(); break;
        case 1: _t->mirrorFixed(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData QG_MirrorOptions::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QG_MirrorOptions::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_QG_MirrorOptions,
      qt_meta_data_QG_MirrorOptions, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QG_MirrorOptions::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QG_MirrorOptions::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QG_MirrorOptions::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QG_MirrorOptions))
        return static_cast<void*>(const_cast< QG_MirrorOptions*>(this));
    return QWidget::qt_metacast(_clname);
}

int QG_MirrorOptions::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
