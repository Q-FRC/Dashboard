/****************************************************************************
** Meta object code from reading C++ file 'NewWidgetTreeDialog.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.6.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../lib/include/dialogs/NewWidgetTreeDialog.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'NewWidgetTreeDialog.h' doesn't include <QObject>."
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
struct qt_meta_stringdata_CLASSNewWidgetTreeDialogENDCLASS_t {};
static constexpr auto qt_meta_stringdata_CLASSNewWidgetTreeDialogENDCLASS = QtMocHelpers::stringData(
    "NewWidgetTreeDialog",
    "widgetReady",
    "",
    "BaseWidget*",
    "widget",
    "WidgetData",
    "data",
    "topicReady",
    "Globals::Topic",
    "topic"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSNewWidgetTreeDialogENDCLASS_t {
    uint offsetsAndSizes[20];
    char stringdata0[20];
    char stringdata1[12];
    char stringdata2[1];
    char stringdata3[12];
    char stringdata4[7];
    char stringdata5[11];
    char stringdata6[5];
    char stringdata7[11];
    char stringdata8[15];
    char stringdata9[6];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSNewWidgetTreeDialogENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSNewWidgetTreeDialogENDCLASS_t qt_meta_stringdata_CLASSNewWidgetTreeDialogENDCLASS = {
    {
        QT_MOC_LITERAL(0, 19),  // "NewWidgetTreeDialog"
        QT_MOC_LITERAL(20, 11),  // "widgetReady"
        QT_MOC_LITERAL(32, 0),  // ""
        QT_MOC_LITERAL(33, 11),  // "BaseWidget*"
        QT_MOC_LITERAL(45, 6),  // "widget"
        QT_MOC_LITERAL(52, 10),  // "WidgetData"
        QT_MOC_LITERAL(63, 4),  // "data"
        QT_MOC_LITERAL(68, 10),  // "topicReady"
        QT_MOC_LITERAL(79, 14),  // "Globals::Topic"
        QT_MOC_LITERAL(94, 5)   // "topic"
    },
    "NewWidgetTreeDialog",
    "widgetReady",
    "",
    "BaseWidget*",
    "widget",
    "WidgetData",
    "data",
    "topicReady",
    "Globals::Topic",
    "topic"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSNewWidgetTreeDialogENDCLASS[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    2,   26,    2, 0x06,    1 /* Public */,
       7,    1,   31,    2, 0x06,    4 /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 5,    4,    6,
    QMetaType::Void, 0x80000000 | 8,    9,

       0        // eod
};

Q_CONSTINIT const QMetaObject NewWidgetTreeDialog::staticMetaObject = { {
    QMetaObject::SuperData::link<QDialog::staticMetaObject>(),
    qt_meta_stringdata_CLASSNewWidgetTreeDialogENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSNewWidgetTreeDialogENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSNewWidgetTreeDialogENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<NewWidgetTreeDialog, std::true_type>,
        // method 'widgetReady'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<BaseWidget *, std::false_type>,
        QtPrivate::TypeAndForceComplete<WidgetData, std::false_type>,
        // method 'topicReady'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const Globals::Topic &, std::false_type>
    >,
    nullptr
} };

void NewWidgetTreeDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<NewWidgetTreeDialog *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->widgetReady((*reinterpret_cast< std::add_pointer_t<BaseWidget*>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<WidgetData>>(_a[2]))); break;
        case 1: _t->topicReady((*reinterpret_cast< std::add_pointer_t<Globals::Topic>>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< BaseWidget* >(); break;
            }
            break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< Globals::Topic >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (NewWidgetTreeDialog::*)(BaseWidget * , WidgetData );
            if (_t _q_method = &NewWidgetTreeDialog::widgetReady; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (NewWidgetTreeDialog::*)(const Globals::Topic & );
            if (_t _q_method = &NewWidgetTreeDialog::topicReady; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject *NewWidgetTreeDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *NewWidgetTreeDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSNewWidgetTreeDialogENDCLASS.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "Ui::NewWidgetTreeDialog"))
        return static_cast< Ui::NewWidgetTreeDialog*>(this);
    return QDialog::qt_metacast(_clname);
}

int NewWidgetTreeDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void NewWidgetTreeDialog::widgetReady(BaseWidget * _t1, WidgetData _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void NewWidgetTreeDialog::topicReady(const Globals::Topic & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
