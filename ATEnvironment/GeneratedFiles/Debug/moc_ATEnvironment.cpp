/****************************************************************************
** Meta object code from reading C++ file 'ATEnvironment.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.1.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../src/ATShell/ATEnvironment.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ATEnvironment.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.1.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_ATEnvironment_t {
    QByteArrayData data[11];
    char stringdata[125];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_ATEnvironment_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_ATEnvironment_t qt_meta_stringdata_ATEnvironment = {
    {
QT_MOC_LITERAL(0, 0, 13),
QT_MOC_LITERAL(1, 14, 16),
QT_MOC_LITERAL(2, 31, 0),
QT_MOC_LITERAL(3, 32, 13),
QT_MOC_LITERAL(4, 46, 14),
QT_MOC_LITERAL(5, 61, 19),
QT_MOC_LITERAL(6, 81, 8),
QT_MOC_LITERAL(7, 90, 11),
QT_MOC_LITERAL(8, 102, 9),
QT_MOC_LITERAL(9, 112, 6),
QT_MOC_LITERAL(10, 119, 4)
    },
    "ATEnvironment\0createNewProject\0\0"
    "createNewFile\0AQProjectNode*\0"
    "project_parent_node\0openFile\0std::string\0"
    "file_name\0AFile*\0file\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ATEnvironment[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   34,    2, 0x0a,
       3,    1,   35,    2, 0x0a,
       6,    1,   38,    2, 0x0a,
       6,    1,   41,    2, 0x0a,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 4,    5,
    QMetaType::Void, 0x80000000 | 7,    8,
    QMetaType::Void, 0x80000000 | 9,   10,

       0        // eod
};

void ATEnvironment::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ATEnvironment *_t = static_cast<ATEnvironment *>(_o);
        switch (_id) {
        case 0: _t->createNewProject(); break;
        case 1: _t->createNewFile((*reinterpret_cast< AQProjectNode*(*)>(_a[1]))); break;
        case 2: _t->openFile((*reinterpret_cast< const std::string(*)>(_a[1]))); break;
        case 3: _t->openFile((*reinterpret_cast< AFile*(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject ATEnvironment::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_ATEnvironment.data,
      qt_meta_data_ATEnvironment,  qt_static_metacall, 0, 0}
};


const QMetaObject *ATEnvironment::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ATEnvironment::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ATEnvironment.stringdata))
        return static_cast<void*>(const_cast< ATEnvironment*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int ATEnvironment::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
