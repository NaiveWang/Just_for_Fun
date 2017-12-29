/****************************************************************************
** Meta object code from reading C++ file 'golcontrolpanel.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../GOLSimulator/golcontrolpanel.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'golcontrolpanel.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_SizeInputDialog_t {
    QByteArrayData data[5];
    char stringdata0[55];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SizeInputDialog_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SizeInputDialog_t qt_meta_stringdata_SizeInputDialog = {
    {
QT_MOC_LITERAL(0, 0, 15), // "SizeInputDialog"
QT_MOC_LITERAL(1, 16, 10), // "dialogOpen"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 12), // "dialogCancel"
QT_MOC_LITERAL(4, 41, 13) // "dialogConfirm"

    },
    "SizeInputDialog\0dialogOpen\0\0dialogCancel\0"
    "dialogConfirm"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SizeInputDialog[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   29,    2, 0x0a /* Public */,
       3,    0,   30,    2, 0x0a /* Public */,
       4,    0,   31,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void SizeInputDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        SizeInputDialog *_t = static_cast<SizeInputDialog *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->dialogOpen(); break;
        case 1: _t->dialogCancel(); break;
        case 2: _t->dialogConfirm(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject SizeInputDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_SizeInputDialog.data,
      qt_meta_data_SizeInputDialog,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *SizeInputDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SizeInputDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_SizeInputDialog.stringdata0))
        return static_cast<void*>(const_cast< SizeInputDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int SizeInputDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}
struct qt_meta_stringdata_GOLControlPanel_t {
    QByteArrayData data[13];
    char stringdata0[109];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_GOLControlPanel_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_GOLControlPanel_t qt_meta_stringdata_GOLControlPanel = {
    {
QT_MOC_LITERAL(0, 0, 15), // "GOLControlPanel"
QT_MOC_LITERAL(1, 16, 7), // "GOLStep"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 6), // "GOLRun"
QT_MOC_LITERAL(4, 32, 8), // "GOLClear"
QT_MOC_LITERAL(5, 41, 7), // "GOLOpen"
QT_MOC_LITERAL(6, 49, 7), // "GOLSave"
QT_MOC_LITERAL(7, 57, 6), // "GOLNew"
QT_MOC_LITERAL(8, 64, 6), // "GOLRan"
QT_MOC_LITERAL(9, 71, 9), // "confColor"
QT_MOC_LITERAL(10, 81, 7), // "confLog"
QT_MOC_LITERAL(11, 89, 9), // "confBound"
QT_MOC_LITERAL(12, 99, 9) // "confCheck"

    },
    "GOLControlPanel\0GOLStep\0\0GOLRun\0"
    "GOLClear\0GOLOpen\0GOLSave\0GOLNew\0GOLRan\0"
    "confColor\0confLog\0confBound\0confCheck"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_GOLControlPanel[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   69,    2, 0x0a /* Public */,
       3,    0,   70,    2, 0x0a /* Public */,
       4,    0,   71,    2, 0x0a /* Public */,
       5,    0,   72,    2, 0x0a /* Public */,
       6,    0,   73,    2, 0x0a /* Public */,
       7,    0,   74,    2, 0x0a /* Public */,
       8,    0,   75,    2, 0x0a /* Public */,
       9,    1,   76,    2, 0x0a /* Public */,
      10,    0,   79,    2, 0x0a /* Public */,
      11,    0,   80,    2, 0x0a /* Public */,
      12,    0,   81,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void GOLControlPanel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        GOLControlPanel *_t = static_cast<GOLControlPanel *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->GOLStep(); break;
        case 1: _t->GOLRun(); break;
        case 2: _t->GOLClear(); break;
        case 3: _t->GOLOpen(); break;
        case 4: _t->GOLSave(); break;
        case 5: _t->GOLNew(); break;
        case 6: _t->GOLRan(); break;
        case 7: _t->confColor((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->confLog(); break;
        case 9: _t->confBound(); break;
        case 10: _t->confCheck(); break;
        default: ;
        }
    }
}

const QMetaObject GOLControlPanel::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_GOLControlPanel.data,
      qt_meta_data_GOLControlPanel,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *GOLControlPanel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *GOLControlPanel::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_GOLControlPanel.stringdata0))
        return static_cast<void*>(const_cast< GOLControlPanel*>(this));
    return QWidget::qt_metacast(_clname);
}

int GOLControlPanel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 11;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
