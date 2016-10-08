/****************************************************************************
** Meta object code from reading C++ file 'qg_leadarcradiusoptions.h'
**
** Created: Mon Sep 26 14:56:10 2016
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../ui/forms/qg_leadarcradiusoptions.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qg_leadarcradiusoptions.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QG_LeadArcRadiusOptions[] = {

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
      30,   25,   24,   24, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_QG_LeadArcRadiusOptions[] = {
    "QG_LeadArcRadiusOptions\0\0strR\0"
    "setRadius(QString)\0"
};

void QG_LeadArcRadiusOptions::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QG_LeadArcRadiusOptions *_t = static_cast<QG_LeadArcRadiusOptions *>(_o);
        switch (_id) {
        case 0: _t->setRadius((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData QG_LeadArcRadiusOptions::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QG_LeadArcRadiusOptions::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_QG_LeadArcRadiusOptions,
      qt_meta_data_QG_LeadArcRadiusOptions, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QG_LeadArcRadiusOptions::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QG_LeadArcRadiusOptions::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QG_LeadArcRadiusOptions::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QG_LeadArcRadiusOptions))
        return static_cast<void*>(const_cast< QG_LeadArcRadiusOptions*>(this));
    return QWidget::qt_metacast(_clname);
}

int QG_LeadArcRadiusOptions::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
