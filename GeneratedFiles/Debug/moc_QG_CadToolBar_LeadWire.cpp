/****************************************************************************
** Meta object code from reading C++ file 'QG_CadToolBar_LeadWire.h'
**
** Created: Mon Sep 26 14:56:10 2016
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../ui/forms/QG_CadToolBar_LeadWire.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'QG_CadToolBar_LeadWire.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QG_CadToolBar_LeadWire[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      24,   23,   23,   23, 0x0a,
      39,   23,   23,   23, 0x0a,
      58,   23,   23,   23, 0x0a,
      77,   23,   23,   23, 0x0a,
     103,   23,   23,   23, 0x0a,
     128,   23,   23,   23, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_QG_CadToolBar_LeadWire[] = {
    "QG_CadToolBar_LeadWire\0\0drawLeadLine()\0"
    "drawLeadLineAuto()\0drawLeadLineSide()\0"
    "drawLeadArcLineVertical()\0"
    "drawLeadArcLineOblique()\0LeadWireReset()\0"
};

void QG_CadToolBar_LeadWire::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QG_CadToolBar_LeadWire *_t = static_cast<QG_CadToolBar_LeadWire *>(_o);
        switch (_id) {
        case 0: _t->drawLeadLine(); break;
        case 1: _t->drawLeadLineAuto(); break;
        case 2: _t->drawLeadLineSide(); break;
        case 3: _t->drawLeadArcLineVertical(); break;
        case 4: _t->drawLeadArcLineOblique(); break;
        case 5: _t->LeadWireReset(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData QG_CadToolBar_LeadWire::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QG_CadToolBar_LeadWire::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_QG_CadToolBar_LeadWire,
      qt_meta_data_QG_CadToolBar_LeadWire, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QG_CadToolBar_LeadWire::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QG_CadToolBar_LeadWire::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QG_CadToolBar_LeadWire::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QG_CadToolBar_LeadWire))
        return static_cast<void*>(const_cast< QG_CadToolBar_LeadWire*>(this));
    return QWidget::qt_metacast(_clname);
}

int QG_CadToolBar_LeadWire::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
QT_END_MOC_NAMESPACE