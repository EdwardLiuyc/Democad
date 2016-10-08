/****************************************************************************
** Meta object code from reading C++ file 'qg_snapmiddleoptions.h'
**
** Created: Mon Sep 26 14:56:09 2016
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../ui/forms/qg_snapmiddleoptions.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qg_snapmiddleoptions.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QG_SnapMiddleOptions[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      32,   22,   21,   21, 0x0a,
      61,   59,   21,   21, 0x2a,
      83,   21,   21,   21, 0x0a,
     104,   21,   21,   21, 0x09,
     126,  121,   21,   21, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_QG_SnapMiddleOptions[] = {
    "QG_SnapMiddleOptions\0\0i,initial\0"
    "setMiddlePoints(int&,bool)\0i\0"
    "setMiddlePoints(int&)\0updateMiddlePoints()\0"
    "languageChange()\0arg1\0"
    "on_sbMiddlePoints_valueChanged(int)\0"
};

void QG_SnapMiddleOptions::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QG_SnapMiddleOptions *_t = static_cast<QG_SnapMiddleOptions *>(_o);
        switch (_id) {
        case 0: _t->setMiddlePoints((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 1: _t->setMiddlePoints((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->updateMiddlePoints(); break;
        case 3: _t->languageChange(); break;
        case 4: _t->on_sbMiddlePoints_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData QG_SnapMiddleOptions::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QG_SnapMiddleOptions::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_QG_SnapMiddleOptions,
      qt_meta_data_QG_SnapMiddleOptions, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QG_SnapMiddleOptions::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QG_SnapMiddleOptions::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QG_SnapMiddleOptions::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QG_SnapMiddleOptions))
        return static_cast<void*>(const_cast< QG_SnapMiddleOptions*>(this));
    if (!strcmp(_clname, "Ui::QG_SnapMiddleOptions"))
        return static_cast< Ui::QG_SnapMiddleOptions*>(const_cast< QG_SnapMiddleOptions*>(this));
    return QWidget::qt_metacast(_clname);
}

int QG_SnapMiddleOptions::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
