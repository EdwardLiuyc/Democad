/****************************************************************************
** Meta object code from reading C++ file 'offsetwdt.h'
**
** Created: Mon Sep 26 14:56:07 2016
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../offsetwdt.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'offsetwdt.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_OffsetWdt[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      11,   10,   10,   10, 0x05,
      30,   26,   10,   10, 0x05,

 // slots: signature, parameters, type, tag, flags
      49,   10,   10,   10, 0x0a,
      66,   10,   10,   10, 0x0a,
      81,   10,   10,   10, 0x0a,
     102,   10,   10,   10, 0x0a,
     131,  122,   10,   10, 0x0a,
     156,   10,   10,   10, 0x0a,
     197,   10,   10,   10, 0x0a,
     216,   10,   10,   10, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_OffsetWdt[] = {
    "OffsetWdt\0\0sglConfigRdy()\0msg\0"
    "sglSetMsg(QString)\0slotBrwSrcFile()\0"
    "slotGenNewNC()\0slotRemoveOffsetXY()\0"
    "slotRemoveOffsetZ()\0filename\0"
    "slotSetDXFFile(QString&)\0"
    "slotGetNewContainer(RS_EntityContainer*)\0"
    "slotCountChanged()\0slotFormatManualOff()\0"
};

void OffsetWdt::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        OffsetWdt *_t = static_cast<OffsetWdt *>(_o);
        switch (_id) {
        case 0: _t->sglConfigRdy(); break;
        case 1: _t->sglSetMsg((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->slotBrwSrcFile(); break;
        case 3: _t->slotGenNewNC(); break;
        case 4: _t->slotRemoveOffsetXY(); break;
        case 5: _t->slotRemoveOffsetZ(); break;
        case 6: _t->slotSetDXFFile((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 7: _t->slotGetNewContainer((*reinterpret_cast< RS_EntityContainer*(*)>(_a[1]))); break;
        case 8: _t->slotCountChanged(); break;
        case 9: _t->slotFormatManualOff(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData OffsetWdt::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject OffsetWdt::staticMetaObject = {
    { &QDockWidget::staticMetaObject, qt_meta_stringdata_OffsetWdt,
      qt_meta_data_OffsetWdt, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &OffsetWdt::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *OffsetWdt::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *OffsetWdt::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_OffsetWdt))
        return static_cast<void*>(const_cast< OffsetWdt*>(this));
    return QDockWidget::qt_metacast(_clname);
}

int OffsetWdt::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDockWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    }
    return _id;
}

// SIGNAL 0
void OffsetWdt::sglConfigRdy()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void OffsetWdt::sglSetMsg(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
