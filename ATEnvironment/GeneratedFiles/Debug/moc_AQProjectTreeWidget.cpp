/****************************************************************************
** Meta object code from reading C++ file 'AQProjectTreeWidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.1.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../src/ATShell/AQProjectTreeWidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'AQProjectTreeWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.1.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_AQProjectTreeWidget_t {
    QByteArrayData data[13];
    char stringdata[192];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_AQProjectTreeWidget_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_AQProjectTreeWidget_t qt_meta_stringdata_AQProjectTreeWidget = {
    {
QT_MOC_LITERAL(0, 0, 19),
QT_MOC_LITERAL(1, 20, 22),
QT_MOC_LITERAL(2, 43, 0),
QT_MOC_LITERAL(3, 44, 14),
QT_MOC_LITERAL(4, 59, 19),
QT_MOC_LITERAL(5, 79, 17),
QT_MOC_LITERAL(6, 97, 6),
QT_MOC_LITERAL(7, 104, 4),
QT_MOC_LITERAL(8, 109, 15),
QT_MOC_LITERAL(9, 125, 3),
QT_MOC_LITERAL(10, 129, 19),
QT_MOC_LITERAL(11, 149, 21),
QT_MOC_LITERAL(12, 171, 19)
    },
    "AQProjectTreeWidget\0createNewFileRequested\0"
    "\0AQProjectNode*\0project_parent_node\0"
    "openFileRequested\0AFile*\0file\0"
    "showContextMenu\0pos\0onRenameItemClicked\0"
    "onAddGroupItemClicked\0onRemoveItemClicked\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_AQProjectTreeWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   44,    2, 0x05,
       5,    1,   47,    2, 0x05,

 // slots: name, argc, parameters, tag, flags
       8,    1,   50,    2, 0x08,
      10,    0,   53,    2, 0x08,
      11,    0,   54,    2, 0x08,
      12,    0,   55,    2, 0x08,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 6,    7,

 // slots: parameters
    QMetaType::Void, QMetaType::QPoint,    9,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void AQProjectTreeWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        AQProjectTreeWidget *_t = static_cast<AQProjectTreeWidget *>(_o);
        switch (_id) {
        case 0: _t->createNewFileRequested((*reinterpret_cast< AQProjectNode*(*)>(_a[1]))); break;
        case 1: _t->openFileRequested((*reinterpret_cast< AFile*(*)>(_a[1]))); break;
        case 2: _t->showContextMenu((*reinterpret_cast< const QPoint(*)>(_a[1]))); break;
        case 3: _t->onRenameItemClicked(); break;
        case 4: _t->onAddGroupItemClicked(); break;
        case 5: _t->onRemoveItemClicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (AQProjectTreeWidget::*_t)(AQProjectNode * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&AQProjectTreeWidget::createNewFileRequested)) {
                *result = 0;
            }
        }
        {
            typedef void (AQProjectTreeWidget::*_t)(AFile * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&AQProjectTreeWidget::openFileRequested)) {
                *result = 1;
            }
        }
    }
}

const QMetaObject AQProjectTreeWidget::staticMetaObject = {
    { &QTreeWidget::staticMetaObject, qt_meta_stringdata_AQProjectTreeWidget.data,
      qt_meta_data_AQProjectTreeWidget,  qt_static_metacall, 0, 0}
};


const QMetaObject *AQProjectTreeWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *AQProjectTreeWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_AQProjectTreeWidget.stringdata))
        return static_cast<void*>(const_cast< AQProjectTreeWidget*>(this));
    return QTreeWidget::qt_metacast(_clname);
}

int AQProjectTreeWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QTreeWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void AQProjectTreeWidget::createNewFileRequested(AQProjectNode * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void AQProjectTreeWidget::openFileRequested(AFile * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
