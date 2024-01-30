/****************************************************************************
** Meta object code from reading C++ file 'WidgetDialogGenerator.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.6.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../lib/include/dialogs/WidgetDialogGenerator.h"
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'WidgetDialogGenerator.h' doesn't include <QObject>."
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
struct qt_meta_stringdata_CLASSWidgetDialogGeneratorENDCLASS_t {};
static constexpr auto qt_meta_stringdata_CLASSWidgetDialogGeneratorENDCLASS = QtMocHelpers::stringData(
    "WidgetDialogGenerator",
    "widgetReady",
    "",
    "BaseWidget*",
    "widget",
    "WidgetData",
    "data",
    "cancelled",
    "topicSelected",
    "Globals::Topic",
    "topic",
    "QWidget*",
    "receiver",
    "colorSelected",
    "color"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSWidgetDialogGeneratorENDCLASS_t {
    uint offsetsAndSizes[30];
    char stringdata0[22];
    char stringdata1[12];
    char stringdata2[1];
    char stringdata3[12];
    char stringdata4[7];
    char stringdata5[11];
    char stringdata6[5];
    char stringdata7[10];
    char stringdata8[14];
    char stringdata9[15];
    char stringdata10[6];
    char stringdata11[9];
    char stringdata12[9];
    char stringdata13[14];
    char stringdata14[6];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSWidgetDialogGeneratorENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSWidgetDialogGeneratorENDCLASS_t qt_meta_stringdata_CLASSWidgetDialogGeneratorENDCLASS = {
    {
        QT_MOC_LITERAL(0, 21),  // "WidgetDialogGenerator"
        QT_MOC_LITERAL(22, 11),  // "widgetReady"
        QT_MOC_LITERAL(34, 0),  // ""
        QT_MOC_LITERAL(35, 11),  // "BaseWidget*"
        QT_MOC_LITERAL(47, 6),  // "widget"
        QT_MOC_LITERAL(54, 10),  // "WidgetData"
        QT_MOC_LITERAL(65, 4),  // "data"
        QT_MOC_LITERAL(70, 9),  // "cancelled"
        QT_MOC_LITERAL(80, 13),  // "topicSelected"
        QT_MOC_LITERAL(94, 14),  // "Globals::Topic"
        QT_MOC_LITERAL(109, 5),  // "topic"
        QT_MOC_LITERAL(115, 8),  // "QWidget*"
        QT_MOC_LITERAL(124, 8),  // "receiver"
        QT_MOC_LITERAL(133, 13),  // "colorSelected"
        QT_MOC_LITERAL(147, 5)   // "color"
    },
    "WidgetDialogGenerator",
    "widgetReady",
    "",
    "BaseWidget*",
    "widget",
    "WidgetData",
    "data",
    "cancelled",
    "topicSelected",
    "Globals::Topic",
    "topic",
    "QWidget*",
    "receiver",
    "colorSelected",
    "color"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSWidgetDialogGeneratorENDCLASS[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    2,   38,    2, 0x06,    1 /* Public */,
       7,    1,   43,    2, 0x06,    4 /* Public */,
       8,    2,   46,    2, 0x06,    6 /* Public */,
      13,    1,   51,    2, 0x06,    9 /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 5,    4,    6,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 9, 0x80000000 | 11,   10,   12,
    QMetaType::Void, QMetaType::QColor,   14,

       0        // eod
};

Q_CONSTINIT const QMetaObject WidgetDialogGenerator::staticMetaObject = { {
    QMetaObject::SuperData::link<QDialog::staticMetaObject>(),
    qt_meta_stringdata_CLASSWidgetDialogGeneratorENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSWidgetDialogGeneratorENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSWidgetDialogGeneratorENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<WidgetDialogGenerator, std::true_type>,
        // method 'widgetReady'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<BaseWidget *, std::false_type>,
        QtPrivate::TypeAndForceComplete<WidgetData, std::false_type>,
        // method 'cancelled'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<BaseWidget *, std::false_type>,
        // method 'topicSelected'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const Globals::Topic &, std::false_type>,
        QtPrivate::TypeAndForceComplete<QWidget *, std::false_type>,
        // method 'colorSelected'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QColor &, std::false_type>
    >,
    nullptr
} };

void WidgetDialogGenerator::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<WidgetDialogGenerator *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->widgetReady((*reinterpret_cast< std::add_pointer_t<BaseWidget*>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<WidgetData>>(_a[2]))); break;
        case 1: _t->cancelled((*reinterpret_cast< std::add_pointer_t<BaseWidget*>>(_a[1]))); break;
        case 2: _t->topicSelected((*reinterpret_cast< std::add_pointer_t<Globals::Topic>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QWidget*>>(_a[2]))); break;
        case 3: _t->colorSelected((*reinterpret_cast< std::add_pointer_t<QColor>>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
        case 2:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< Globals::Topic >(); break;
            case 1:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QWidget* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (WidgetDialogGenerator::*)(BaseWidget * , WidgetData );
            if (_t _q_method = &WidgetDialogGenerator::widgetReady; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (WidgetDialogGenerator::*)(BaseWidget * );
            if (_t _q_method = &WidgetDialogGenerator::cancelled; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (WidgetDialogGenerator::*)(const Globals::Topic & , QWidget * );
            if (_t _q_method = &WidgetDialogGenerator::topicSelected; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (WidgetDialogGenerator::*)(const QColor & );
            if (_t _q_method = &WidgetDialogGenerator::colorSelected; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 3;
                return;
            }
        }
    }
}

const QMetaObject *WidgetDialogGenerator::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *WidgetDialogGenerator::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSWidgetDialogGeneratorENDCLASS.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "Ui::WidgetDialogGenerator"))
        return static_cast< Ui::WidgetDialogGenerator*>(this);
    return QDialog::qt_metacast(_clname);
}

int WidgetDialogGenerator::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void WidgetDialogGenerator::widgetReady(BaseWidget * _t1, WidgetData _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void WidgetDialogGenerator::cancelled(BaseWidget * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void WidgetDialogGenerator::topicSelected(const Globals::Topic & _t1, QWidget * _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void WidgetDialogGenerator::colorSelected(const QColor & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_WARNING_POP
