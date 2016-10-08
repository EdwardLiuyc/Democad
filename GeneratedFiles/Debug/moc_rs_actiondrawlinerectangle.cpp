/****************************************************************************
** Meta object code from reading C++ file 'rs_actiondrawlinerectangle.h'
**
** Created: Mon Sep 26 14:56:08 2016
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../actions/rs_actiondrawlinerectangle.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'rs_actiondrawlinerectangle.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_RS_ActionDrawLineRectangle[] = {

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
      34,   28,   27,   27, 0x0a,
      54,   52,   27,   27, 0x0a,
      71,   52,   27,   27, 0x0a,
      87,   52,   27,   27, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_RS_ActionDrawLineRectangle[] = {
    "RS_ActionDrawLineRectangle\0\0mpost\0"
    "OnCommit(MyPoint)\0f\0OnRight(QString)\0"
    "OnLeft(QString)\0OnEnter(QString)\0"
};

void RS_ActionDrawLineRectangle::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        RS_ActionDrawLineRectangle *_t = static_cast<RS_ActionDrawLineRectangle *>(_o);
        switch (_id) {
        case 0: _t->OnCommit((*reinterpret_cast< MyPoint(*)>(_a[1]))); break;
        case 1: _t->OnRight((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->OnLeft((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: _t->OnEnter((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData RS_ActionDrawLineRectangle::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject RS_ActionDrawLineRectangle::staticMetaObject = {
    { &RS_PreviewActionInterface::staticMetaObject, qt_meta_stringdata_RS_ActionDrawLineRectangle,
      qt_meta_data_RS_ActionDrawLineRectangle, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &RS_ActionDrawLineRectangle::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *RS_ActionDrawLineRectangle::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *RS_ActionDrawLineRectangle::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_RS_ActionDrawLineRectangle))
        return static_cast<void*>(const_cast< RS_ActionDrawLineRectangle*>(this));
    return RS_PreviewActionInterface::qt_metacast(_clname);
}

int RS_ActionDrawLineRectangle::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = RS_PreviewActionInterface::qt_metacall(_c, _id, _a);
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
