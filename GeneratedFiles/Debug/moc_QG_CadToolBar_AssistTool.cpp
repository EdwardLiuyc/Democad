/****************************************************************************
** Meta object code from reading C++ file 'QG_CadToolBar_AssistTool.h'
**
** Created: Mon Sep 26 14:56:11 2016
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../ui/forms/QG_CadToolBar_AssistTool.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'QG_CadToolBar_AssistTool.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QG_CadToolBar_AssistTool[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      26,   25,   25,   25, 0x0a,
      38,   25,   25,   25, 0x0a,
      55,   25,   25,   25, 0x0a,
      71,   25,   25,   25, 0x0a,
      83,   25,   25,   25, 0x0a,
      93,   25,   25,   25, 0x0a,
     103,   25,   25,   25, 0x0a,
     117,   25,   25,   25, 0x0a,
     132,   25,   25,   25, 0x0a,
     145,   25,   25,   25, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_QG_CadToolBar_AssistTool[] = {
    "QG_CadToolBar_AssistTool\0\0ShowValue()\0"
    "Distance_Point()\0Distance_Cell()\0"
    "ShowAngle()\0GridSet()\0SizeSet()\0"
    "OriginalSet()\0OriginalInit()\0FullScreen()\0"
    "AssistToolReset()\0"
};

void QG_CadToolBar_AssistTool::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QG_CadToolBar_AssistTool *_t = static_cast<QG_CadToolBar_AssistTool *>(_o);
        switch (_id) {
        case 0: _t->ShowValue(); break;
        case 1: _t->Distance_Point(); break;
        case 2: _t->Distance_Cell(); break;
        case 3: _t->ShowAngle(); break;
        case 4: _t->GridSet(); break;
        case 5: _t->SizeSet(); break;
        case 6: _t->OriginalSet(); break;
        case 7: _t->OriginalInit(); break;
        case 8: _t->FullScreen(); break;
        case 9: _t->AssistToolReset(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData QG_CadToolBar_AssistTool::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QG_CadToolBar_AssistTool::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_QG_CadToolBar_AssistTool,
      qt_meta_data_QG_CadToolBar_AssistTool, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QG_CadToolBar_AssistTool::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QG_CadToolBar_AssistTool::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QG_CadToolBar_AssistTool::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QG_CadToolBar_AssistTool))
        return static_cast<void*>(const_cast< QG_CadToolBar_AssistTool*>(this));
    return QWidget::qt_metacast(_clname);
}

int QG_CadToolBar_AssistTool::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
