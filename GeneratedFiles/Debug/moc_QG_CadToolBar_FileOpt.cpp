/****************************************************************************
** Meta object code from reading C++ file 'QG_CadToolBar_FileOpt.h'
**
** Created: Mon Sep 26 14:56:10 2016
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../ui/forms/QG_CadToolBar_FileOpt.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'QG_CadToolBar_FileOpt.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QG_CadToolBar_FileOpt[] = {

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
      23,   22,   22,   22, 0x0a,
      33,   22,   22,   22, 0x0a,
      42,   22,   22,   22, 0x0a,
      52,   22,   22,   22, 0x0a,
      64,   22,   22,   22, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_QG_CadToolBar_FileOpt[] = {
    "QG_CadToolBar_FileOpt\0\0OpenOpt()\0"
    "NewOpt()\0SaveOpt()\0SaveAsOpt()\0"
    "fileOptReset()\0"
};

void QG_CadToolBar_FileOpt::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QG_CadToolBar_FileOpt *_t = static_cast<QG_CadToolBar_FileOpt *>(_o);
        switch (_id) {
        case 0: _t->OpenOpt(); break;
        case 1: _t->NewOpt(); break;
        case 2: _t->SaveOpt(); break;
        case 3: _t->SaveAsOpt(); break;
        case 4: _t->fileOptReset(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData QG_CadToolBar_FileOpt::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QG_CadToolBar_FileOpt::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_QG_CadToolBar_FileOpt,
      qt_meta_data_QG_CadToolBar_FileOpt, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QG_CadToolBar_FileOpt::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QG_CadToolBar_FileOpt::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QG_CadToolBar_FileOpt::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QG_CadToolBar_FileOpt))
        return static_cast<void*>(const_cast< QG_CadToolBar_FileOpt*>(this));
    return QWidget::qt_metacast(_clname);
}

int QG_CadToolBar_FileOpt::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
