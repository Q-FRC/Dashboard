/****************************************************************************
** Meta object code from reading C++ file 'TypeStore.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.6.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../lib/include/stores/TypeStore.h"
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'TypeStore.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.6.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {

#ifdef QT_MOC_HAS_STRINGDATA
struct qt_meta_stringdata_CLASSTypeStoreENDCLASS_t {};
static constexpr auto qt_meta_stringdata_CLASSTypeStoreENDCLASS = QtMocHelpers::stringData(
    "TypeStore",
    "widgetReady",
    "",
    "BaseWidget*",
    "widget",
    "WidgetData",
    "data",
    "emitWidget"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSTypeStoreENDCLASS_t {
    uint offsetsAndSizes[16];
    char stringdata0[10];
    char stringdata1[12];
    char stringdata2[1];
    char stringdata3[12];
    char stringdata4[7];
    char stringdata5[11];
    char stringdata6[5];
    char stringdata7[11];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSTypeStoreENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSTypeStoreENDCLASS_t qt_meta_stringdata_CLASSTypeStoreENDCLASS = {
    {
        QT_MOC_LITERAL(0, 9),  // "TypeStore"
        QT_MOC_LITERAL(10, 11),  // "widgetReady"
        QT_MOC_LITERAL(22, 0),  // ""
        QT_MOC_LITERAL(23, 11),  // "BaseWidget*"
        QT_MOC_LITERAL(35, 6),  // "widget"
        QT_MOC_LITERAL(42, 10),  // "WidgetData"
        QT_MOC_LITERAL(53, 4),  // "data"
        QT_MOC_LITERAL(58, 10)   // "emitWidget"
    },
    "TypeStore",
    "widgetReady",
    "",
    "BaseWidget*",
    "widget",
    "WidgetData",
    "data",
    "emitWidget"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSTypeStoreENDCLASS[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    2,   26,    2, 0x06,    1 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       7,    2,   31,    2, 0x0a,    4 /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 5,    4,    6,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 5,    4,    6,

       0        // eod
};

Q_CONSTINIT const QMetaObject TypeStore::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_CLASSTypeStoreENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSTypeStoreENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSTypeStoreENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<TypeStore, std::true_type>,
        // method 'widgetReady'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<BaseWidget *, std::false_type>,
        QtPrivate::TypeAndForceComplete<WidgetData, std::false_type>,
        // method 'emitWidget'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<BaseWidget *, std::false_type>,
        QtPrivate::TypeAndForceComplete<WidgetData, std::false_type>
    >,
    nullptr
} };

void TypeStore::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<TypeStore *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->widgetReady((*reinterpret_cast< std::add_pointer_t<BaseWidget*>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<WidgetData>>(_a[2]))); break;
        case 1: _t->emitWidget((*reinterpret_cast< std::add_pointer_t<BaseWidget*>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<WidgetData>>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (TypeStore::*)(BaseWidget * , WidgetData );
            if (_t _q_method = &TypeStore::widgetReady; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject *TypeStore::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TypeStore::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSTypeStoreENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int TypeStore::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void TypeStore::widgetReady(BaseWidget * _t1, WidgetData _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
