/****************************************************************************
** Meta object code from reading C++ file 'qg_actionhandler.h'
**
** Created: Mon Sep 26 14:56:09 2016
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../ui/qg_actionhandler.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qg_actionhandler.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QG_ActionHandler[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      38,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      24,   18,   17,   17, 0x0a,
      95,   76,   17,   17, 0x0a,
     140,  132,   17,   17, 0x0a,
     169,   17,   17,   17, 0x0a,
     192,   17,   17,   17, 0x0a,
     211,   17,   17,   17, 0x0a,
     234,   17,   17,   17, 0x0a,
     264,   17,   17,   17, 0x0a,
     293,   17,   17,   17, 0x0a,
     306,   17,   17,   17, 0x0a,
     320,   17,   17,   17, 0x0a,
     335,   17,   17,   17, 0x0a,
     350,   17,   17,   17, 0x0a,
     366,   17,   17,   17, 0x0a,
     384,   17,   17,   17, 0x0a,
     423,   17,  403,   17, 0x0a,
     438,   17,  403,   17, 0x0a,
     462,   17,   17,   17, 0x0a,
     479,   17,   17,   17, 0x0a,
     493,   17,   17,   17, 0x0a,
     517,   17,   17,   17, 0x0a,
     534,   17,   17,   17, 0x0a,
     552,   17,   17,   17, 0x0a,
     571,   17,   17,   17, 0x0a,
     590,   17,   17,   17, 0x0a,
     607,   17,   17,   17, 0x0a,
     625,   17,   17,   17, 0x0a,
     651,   17,   17,   17, 0x0a,
     683,  680,   17,   17, 0x0a,
     715,   17,   17,   17, 0x0a,
     732,   17,   17,   17, 0x0a,
     750,   17,   17,   17, 0x0a,
     767,   17,   17,   17, 0x0a,
     789,   17,   17,   17, 0x0a,
     805,   17,   17,   17, 0x0a,
     821,   17,   17,   17, 0x0a,
     841,   17,   17,   17, 0x0a,
     859,   17,   17,   17, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_QG_ActionHandler[] = {
    "QG_ActionHandler\0\0rs_ai\0"
    "getSglActionLinkClearUP(QList<RS_ActionInterface*>)\0"
    "iTprD,dTprAF,dTprA\0"
    "slotSetPartTaperV(int,double,double)\0"
    "bAR,dAR\0slotSetAssignRV(bool,double)\0"
    "slotAutoDrawLeadLine()\0slotDrawLeadLine()\0"
    "slotDrawLeadLineSide()\0"
    "slotDrawLeadArcLineVertical()\0"
    "slotDrawLeadArcLineOblique()\0slotZoomIn()\0"
    "slotZoomOut()\0slotEditUndo()\0"
    "slotEditRedo()\0slotSelectAll()\0"
    "slotDeselectAll()\0slotSelectInvert()\0"
    "RS_ActionInterface*\0slotDrawLine()\0"
    "slotDrawLineRectangle()\0slotDrawCircle()\0"
    "slotDrawArc()\0slotModifyDeleteQuick()\0"
    "slotModifyMove()\0slotModifyScale()\0"
    "slotModifyRotate()\0slotModifyMirror()\0"
    "slotModifyTrim()\0slotModifyTrim2()\0"
    "slotSetSnaps(RS_SnapMode)\0"
    "updateSnapMode(RS_SnapMode&)\0tb\0"
    "setSnapToolBar(QG_SnapToolBar*)\0"
    "slotcalDisOfTP()\0slotshowPosOfTP()\0"
    "slotfullScreen()\0slotshowMinDistance()\0"
    "slotshowAngel()\0slotoriginSet()\0"
    "slotoriginInitial()\0slotSizeInitial()\0"
    "slotsetGridType()\0"
};

void QG_ActionHandler::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QG_ActionHandler *_t = static_cast<QG_ActionHandler *>(_o);
        switch (_id) {
        case 0: _t->getSglActionLinkClearUP((*reinterpret_cast< QList<RS_ActionInterface*>(*)>(_a[1]))); break;
        case 1: _t->slotSetPartTaperV((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2])),(*reinterpret_cast< double(*)>(_a[3]))); break;
        case 2: _t->slotSetAssignRV((*reinterpret_cast< bool(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2]))); break;
        case 3: _t->slotAutoDrawLeadLine(); break;
        case 4: _t->slotDrawLeadLine(); break;
        case 5: _t->slotDrawLeadLineSide(); break;
        case 6: _t->slotDrawLeadArcLineVertical(); break;
        case 7: _t->slotDrawLeadArcLineOblique(); break;
        case 8: _t->slotZoomIn(); break;
        case 9: _t->slotZoomOut(); break;
        case 10: _t->slotEditUndo(); break;
        case 11: _t->slotEditRedo(); break;
        case 12: _t->slotSelectAll(); break;
        case 13: _t->slotDeselectAll(); break;
        case 14: _t->slotSelectInvert(); break;
        case 15: { RS_ActionInterface* _r = _t->slotDrawLine();
            if (_a[0]) *reinterpret_cast< RS_ActionInterface**>(_a[0]) = _r; }  break;
        case 16: { RS_ActionInterface* _r = _t->slotDrawLineRectangle();
            if (_a[0]) *reinterpret_cast< RS_ActionInterface**>(_a[0]) = _r; }  break;
        case 17: _t->slotDrawCircle(); break;
        case 18: _t->slotDrawArc(); break;
        case 19: _t->slotModifyDeleteQuick(); break;
        case 20: _t->slotModifyMove(); break;
        case 21: _t->slotModifyScale(); break;
        case 22: _t->slotModifyRotate(); break;
        case 23: _t->slotModifyMirror(); break;
        case 24: _t->slotModifyTrim(); break;
        case 25: _t->slotModifyTrim2(); break;
        case 26: _t->slotSetSnaps((*reinterpret_cast< RS_SnapMode(*)>(_a[1]))); break;
        case 27: _t->updateSnapMode((*reinterpret_cast< RS_SnapMode(*)>(_a[1]))); break;
        case 28: _t->setSnapToolBar((*reinterpret_cast< QG_SnapToolBar*(*)>(_a[1]))); break;
        case 29: _t->slotcalDisOfTP(); break;
        case 30: _t->slotshowPosOfTP(); break;
        case 31: _t->slotfullScreen(); break;
        case 32: _t->slotshowMinDistance(); break;
        case 33: _t->slotshowAngel(); break;
        case 34: _t->slotoriginSet(); break;
        case 35: _t->slotoriginInitial(); break;
        case 36: _t->slotSizeInitial(); break;
        case 37: _t->slotsetGridType(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData QG_ActionHandler::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QG_ActionHandler::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_QG_ActionHandler,
      qt_meta_data_QG_ActionHandler, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QG_ActionHandler::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QG_ActionHandler::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QG_ActionHandler::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QG_ActionHandler))
        return static_cast<void*>(const_cast< QG_ActionHandler*>(this));
    return QObject::qt_metacast(_clname);
}

int QG_ActionHandler::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 38)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 38;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
