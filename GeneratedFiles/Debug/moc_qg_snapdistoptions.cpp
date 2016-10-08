/****************************************************************************
** Meta object code from reading C++ file 'qg_snapdistoptions.h'
**
** Created: Mon Sep 26 14:56:09 2016
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../ui/forms/qg_snapdistoptions.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qg_snapdistoptions.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QG_SnapDistOptions[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      30,   20,   19,   19, 0x0a,
      54,   52,   19,   19, 0x2a,
      71,   52,   19,   19, 0x0a,
      91,   19,   19,   19, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_QG_SnapDistOptions[] = {
    "QG_SnapDistOptions\0\0d,initial\0"
    "setDist(double&,bool)\0d\0setDist(double&)\0"
    "updateDist(QString)\0languageChange()\0"
};

void QG_SnapDistOptions::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QG_SnapDistOptions *_t = static_cast<QG_SnapDistOptions *>(_o);
        switch (_id) {
        case 0: _t->setDist((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 1: _t->setDist((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 2: _t->updateDist((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 3: _t->languageChange(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData QG_SnapDistOptions::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QG_SnapDistOptions::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_QG_SnapDistOptions,
      qt_meta_data_QG_SnapDistOptions, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QG_SnapDistOptions::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QG_SnapDistOptions::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QG_SnapDistOptions::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QG_SnapDistOptions))
        return static_cast<void*>(const_cast< QG_SnapDistOptions*>(this));
    if (!strcmp(_clname, "Ui::QG_SnapDistOptions"))
        return static_cast< Ui::QG_SnapDistOptions*>(const_cast< QG_SnapDistOptions*>(this));
    return QWidget::qt_metacast(_clname);
}

int QG_SnapDistOptions::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
