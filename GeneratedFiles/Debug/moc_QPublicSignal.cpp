/****************************************************************************
** Meta object code from reading C++ file 'QPublicSignal.h'
**
** Created: Mon Sep 26 14:56:09 2016
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../cadextra/QPublicSignal.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'QPublicSignal.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QPublicSignal[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      14,       // signalCount

 // signals: signature, parameters, type, tag, flags
      15,   14,   14,   14, 0x05,
      46,   42,   14,   14, 0x05,
      71,   14,   14,   14, 0x05,
      91,   14,   14,   14, 0x05,
     106,   14,   14,   14, 0x05,
     133,   14,   14,   14, 0x05,
     163,  157,   14,   14, 0x05,
     212,   14,   14,   14, 0x05,
     233,   14,   14,   14, 0x05,
     246,   14,   14,   14, 0x05,
     258,   14,   14,   14, 0x05,
     271,   14,   14,   14, 0x05,
     286,   14,   14,   14, 0x05,
     304,   14,   14,   14, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_QPublicSignal[] = {
    "QPublicSignal\0\0SglDemoCadFullScreenExit()\0"
    "nMs\0StartTrancingThread(int)\0"
    "EndTrancingThread()\0getGIDSgl(int)\0"
    "SglDemoCadFullScreen(bool)\0"
    "SglPromFullScreen(bool)\0rs_ai\0"
    "SglActionLinkClearUP(QList<RS_ActionInterface*>)\0"
    "SglSendClearChoise()\0SglOpenOpt()\0"
    "SglNewOpt()\0SglSaveOpt()\0SglSaveAsOpt()\0"
    "SglDemoCadReset()\0"
    "SglGetNewContainer(RS_EntityContainer*)\0"
};

void QPublicSignal::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QPublicSignal *_t = static_cast<QPublicSignal *>(_o);
        switch (_id) {
        case 0: _t->SglDemoCadFullScreenExit(); break;
        case 1: _t->StartTrancingThread((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->EndTrancingThread(); break;
        case 3: _t->getGIDSgl((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->SglDemoCadFullScreen((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 5: _t->SglPromFullScreen((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 6: _t->SglActionLinkClearUP((*reinterpret_cast< QList<RS_ActionInterface*>(*)>(_a[1]))); break;
        case 7: _t->SglSendClearChoise(); break;
        case 8: _t->SglOpenOpt(); break;
        case 9: _t->SglNewOpt(); break;
        case 10: _t->SglSaveOpt(); break;
        case 11: _t->SglSaveAsOpt(); break;
        case 12: _t->SglDemoCadReset(); break;
        case 13: _t->SglGetNewContainer((*reinterpret_cast< RS_EntityContainer*(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData QPublicSignal::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QPublicSignal::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_QPublicSignal,
      qt_meta_data_QPublicSignal, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QPublicSignal::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QPublicSignal::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QPublicSignal::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QPublicSignal))
        return static_cast<void*>(const_cast< QPublicSignal*>(this));
    return QObject::qt_metacast(_clname);
}

int QPublicSignal::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    }
    return _id;
}

// SIGNAL 0
void QPublicSignal::SglDemoCadFullScreenExit()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void QPublicSignal::StartTrancingThread(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void QPublicSignal::EndTrancingThread()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}

// SIGNAL 3
void QPublicSignal::getGIDSgl(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void QPublicSignal::SglDemoCadFullScreen(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void QPublicSignal::SglPromFullScreen(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void QPublicSignal::SglActionLinkClearUP(QList<RS_ActionInterface*> _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void QPublicSignal::SglSendClearChoise()
{
    QMetaObject::activate(this, &staticMetaObject, 7, 0);
}

// SIGNAL 8
void QPublicSignal::SglOpenOpt()
{
    QMetaObject::activate(this, &staticMetaObject, 8, 0);
}

// SIGNAL 9
void QPublicSignal::SglNewOpt()
{
    QMetaObject::activate(this, &staticMetaObject, 9, 0);
}

// SIGNAL 10
void QPublicSignal::SglSaveOpt()
{
    QMetaObject::activate(this, &staticMetaObject, 10, 0);
}

// SIGNAL 11
void QPublicSignal::SglSaveAsOpt()
{
    QMetaObject::activate(this, &staticMetaObject, 11, 0);
}

// SIGNAL 12
void QPublicSignal::SglDemoCadReset()
{
    QMetaObject::activate(this, &staticMetaObject, 12, 0);
}

// SIGNAL 13
void QPublicSignal::SglGetNewContainer(RS_EntityContainer * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 13, _a);
}
QT_END_MOC_NAMESPACE
