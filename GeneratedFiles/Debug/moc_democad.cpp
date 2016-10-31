/****************************************************************************
** Meta object code from reading C++ file 'democad.h'
**
** Created: Tue Oct 25 09:10:52 2016
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../democad.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'democad.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_DemoCad[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      18,    9,    8,    8, 0x05,

 // slots: signature, parameters, type, tag, flags
      50,   43,    8,    8, 0x0a,
      73,   69,    8,    8, 0x0a,
      93,    8,    8,    8, 0x0a,
     109,    8,  104,    8, 0x0a,
     120,    8,  104,    8, 0x0a,
     133,    8,    8,    8, 0x0a,
     143,    8,    8,    8, 0x0a,
     161,    8,    8,    8, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_DemoCad[] = {
    "DemoCad\0\0filename\0sglOpenDXFFile(QString&)\0"
    "toggle\0slotViewGrid(bool)\0msg\0"
    "slotSetMsg(QString)\0openFile()\0bool\0"
    "saveFile()\0saveAsFile()\0newFile()\0"
    "slotThisVis(bool)\0slotReset232()\0"
};

void DemoCad::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        DemoCad *_t = static_cast<DemoCad *>(_o);
        switch (_id) {
        case 0: _t->sglOpenDXFFile((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->slotViewGrid((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: _t->slotSetMsg((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: _t->openFile(); break;
        case 4: { bool _r = _t->saveFile();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 5: { bool _r = _t->saveAsFile();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 6: _t->newFile(); break;
        case 7: _t->slotThisVis((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 8: _t->slotReset232(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData DemoCad::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject DemoCad::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_DemoCad,
      qt_meta_data_DemoCad, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &DemoCad::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *DemoCad::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *DemoCad::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_DemoCad))
        return static_cast<void*>(const_cast< DemoCad*>(this));
    if (!strcmp(_clname, "QG_MainWindowInterface"))
        return static_cast< QG_MainWindowInterface*>(const_cast< DemoCad*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int DemoCad::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void DemoCad::sglOpenDXFFile(QString & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
