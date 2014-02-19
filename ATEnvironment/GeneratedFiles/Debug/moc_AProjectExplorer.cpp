/****************************************************************************
** Meta object code from reading C++ file 'AProjectExplorer.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.1.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../src/ATShell/AProjectExplorer.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'AProjectExplorer.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.1.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_AProjectExplorer_t {
    QByteArrayData data[8];
    char stringdata[107];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_AProjectExplorer_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_AProjectExplorer_t qt_meta_stringdata_AProjectExplorer = {
    {
QT_MOC_LITERAL(0, 0, 16),
QT_MOC_LITERAL(1, 17, 22),
QT_MOC_LITERAL(2, 40, 0),
QT_MOC_LITERAL(3, 41, 14),
QT_MOC_LITERAL(4, 56, 19),
QT_MOC_LITERAL(5, 76, 17),
QT_MOC_LITERAL(6, 94, 6),
QT_MOC_LITERAL(7, 101, 4)
    },
    "AProjectExplorer\0createNewFileRequested\0"
    "\0AQProjectNode*\0project_parent_node\0"
    "openFileRequested\0AFile*\0file\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_AProjectExplorer[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   24,    2, 0x05,
       5,    1,   27,    2, 0x05,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 6,    7,

       0        // eod
};

void AProjectExplorer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        AProjectExplorer *_t = static_cast<AProjectExplorer *>(_o);
        switch (_id) {
        case 0: _t->createNewFileRequested((*reinterpret_cast< AQProjectNode*(*)>(_a[1]))); break;
        case 1: _t->openFileRequested((*reinterpret_cast< AFile*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (AProjectExplorer::*_t)(AQProjectNode * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&AProjectExplorer::createNewFileRequested)) {
                *result = 0;
            }
        }
        {
            typedef void (AProjectExplorer::*_t)(AFile * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&AProjectExplorer::openFileRequested)) {
                *result = 1;
            }
        }
    }
}

const QMetaObject AProjectExplorer::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_AProjectExplorer.data,
      qt_meta_data_AProjectExplorer,  qt_static_metacall, 0, 0}
};


const QMetaObject *AProjectExplorer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *AProjectExplorer::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_AProjectExplorer.stringdata))
        return static_cast<void*>(const_cast< AProjectExplorer*>(this));
    return QWidget::qt_metacast(_clname);
}

int AProjectExplorer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void AProjectExplorer::createNewFileRequested(AQProjectNode * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void AProjectExplorer::openFileRequested(AFile * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
