/****************************************************************************
** Meta object code from reading C++ file 'qg_cadtoolbarmain.h'
**
** Created: Mon Sep 26 14:56:10 2016
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../ui/forms/qg_cadtoolbarmain.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qg_cadtoolbarmain.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QG_CadToolBarMain[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      18,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      19,   18,   18,   18, 0x0a,
      26,   18,   18,   18, 0x0a,
      37,   18,   18,   18, 0x0a,
      57,   18,   18,   18, 0x0a,
      70,   18,   18,   18, 0x0a,
      80,   18,   18,   18, 0x0a,
      94,   18,   18,   18, 0x0a,
     106,   18,   18,   18, 0x0a,
     121,   18,   18,   18, 0x0a,
     134,   18,   18,   18, 0x0a,
     148,   18,   18,   18, 0x0a,
     161,   18,   18,   18, 0x0a,
     176,   18,   18,   18, 0x0a,
     190,   18,   18,   18, 0x0a,
     205,   18,   18,   18, 0x0a,
     220,   18,   18,   18, 0x0a,
     240,   18,   18,   18, 0x0a,
     254,   18,   18,   18, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_QG_CadToolBarMain[] = {
    "QG_CadToolBarMain\0\0init()\0drawLine()\0"
    "drawLineRectangle()\0drawCircle()\0"
    "drawArc()\0deselectAll()\0selectAll()\0"
    "selectInvert()\0modifyTrim()\0modifyTrim2()\0"
    "modifyMove()\0modifyRotate()\0modifyScale()\0"
    "modifyMirror()\0modifydelete()\0"
    "getFullScreenExit()\0OnEditReset()\0"
    "languageChange()\0"
};

void QG_CadToolBarMain::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QG_CadToolBarMain *_t = static_cast<QG_CadToolBarMain *>(_o);
        switch (_id) {
        case 0: _t->init(); break;
        case 1: _t->drawLine(); break;
        case 2: _t->drawLineRectangle(); break;
        case 3: _t->drawCircle(); break;
        case 4: _t->drawArc(); break;
        case 5: _t->deselectAll(); break;
        case 6: _t->selectAll(); break;
        case 7: _t->selectInvert(); break;
        case 8: _t->modifyTrim(); break;
        case 9: _t->modifyTrim2(); break;
        case 10: _t->modifyMove(); break;
        case 11: _t->modifyRotate(); break;
        case 12: _t->modifyScale(); break;
        case 13: _t->modifyMirror(); break;
        case 14: _t->modifydelete(); break;
        case 15: _t->getFullScreenExit(); break;
        case 16: _t->OnEditReset(); break;
        case 17: _t->languageChange(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData QG_CadToolBarMain::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QG_CadToolBarMain::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_QG_CadToolBarMain,
      qt_meta_data_QG_CadToolBarMain, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QG_CadToolBarMain::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QG_CadToolBarMain::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QG_CadToolBarMain::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QG_CadToolBarMain))
        return static_cast<void*>(const_cast< QG_CadToolBarMain*>(this));
    if (!strcmp(_clname, "Ui::QG_CadToolBarMain"))
        return static_cast< Ui::QG_CadToolBarMain*>(const_cast< QG_CadToolBarMain*>(this));
    return QWidget::qt_metacast(_clname);
}

int QG_CadToolBarMain::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 18)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 18;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
