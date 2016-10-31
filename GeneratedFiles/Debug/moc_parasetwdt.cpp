/****************************************************************************
** Meta object code from reading C++ file 'parasetwdt.h'
**
** Created: Tue Oct 18 14:45:11 2016
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../parasetwdt.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'parasetwdt.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ParaSetWdt[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x05,
      34,   30,   11,   11, 0x05,

 // slots: signature, parameters, type, tag, flags
      53,   11,   11,   11, 0x0a,
      70,   11,   11,   11, 0x0a,
      89,   11,   11,   11, 0x0a,
     102,   11,   11,   11, 0x0a,
     116,   11,   11,   11, 0x0a,
     135,   11,   11,   11, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_ParaSetWdt[] = {
    "ParaSetWdt\0\0sglCountChanged()\0msg\0"
    "sglSetMsg(QString)\0slotCalAndSave()\0"
    "slotRadSetFinish()\0slotConfig()\0"
    "slotInOrOut()\0slotInputSetting()\0"
    "slotShowAllQ()\0"
};

void ParaSetWdt::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ParaSetWdt *_t = static_cast<ParaSetWdt *>(_o);
        switch (_id) {
        case 0: _t->sglCountChanged(); break;
        case 1: _t->sglSetMsg((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->slotCalAndSave(); break;
        case 3: _t->slotRadSetFinish(); break;
        case 4: _t->slotConfig(); break;
        case 5: _t->slotInOrOut(); break;
        case 6: _t->slotInputSetting(); break;
        case 7: _t->slotShowAllQ(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData ParaSetWdt::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ParaSetWdt::staticMetaObject = {
    { &QDockWidget::staticMetaObject, qt_meta_stringdata_ParaSetWdt,
      qt_meta_data_ParaSetWdt, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ParaSetWdt::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ParaSetWdt::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ParaSetWdt::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ParaSetWdt))
        return static_cast<void*>(const_cast< ParaSetWdt*>(this));
    return QDockWidget::qt_metacast(_clname);
}

int ParaSetWdt::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDockWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void ParaSetWdt::sglCountChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void ParaSetWdt::sglSetMsg(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
