/****************************************************************************
** Meta object code from reading C++ file 'getData_Line.h'
**
** Created: Mon Sep 26 14:56:11 2016
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../ui/forms/getData_Line.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'getData_Line.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_getData_Line[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: signature, parameters, type, tag, flags
      20,   14,   13,   13, 0x05,
      38,   36,   13,   13, 0x05,
      53,   36,   13,   13, 0x05,
      68,   36,   13,   13, 0x05,

 // slots: signature, parameters, type, tag, flags
      82,   13,   13,   13, 0x0a,
      92,   13,   13,   13, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_getData_Line[] = {
    "getData_Line\0\0mpost\0commit(MyPoint)\0"
    "f\0Enter(QString)\0Right(QString)\0"
    "Left(QString)\0DoInput()\0Init()\0"
};

void getData_Line::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        getData_Line *_t = static_cast<getData_Line *>(_o);
        switch (_id) {
        case 0: _t->commit((*reinterpret_cast< MyPoint(*)>(_a[1]))); break;
        case 1: _t->Enter((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->Right((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: _t->Left((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: _t->DoInput(); break;
        case 5: _t->Init(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData getData_Line::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject getData_Line::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_getData_Line,
      qt_meta_data_getData_Line, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &getData_Line::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *getData_Line::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *getData_Line::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_getData_Line))
        return static_cast<void*>(const_cast< getData_Line*>(this));
    return QWidget::qt_metacast(_clname);
}

int getData_Line::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void getData_Line::commit(MyPoint _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void getData_Line::Enter(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void getData_Line::Right(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void getData_Line::Left(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_END_MOC_NAMESPACE
