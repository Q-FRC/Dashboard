/****************************************************************************
** Meta object code from reading C++ file 'IntegerDialWidget.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.6.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../lib/include/widgets/IntegerDialWidget.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'IntegerDialWidget.h' doesn't include <QObject>."
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
struct qt_meta_stringdata_CLASSIntegerDialWidgetENDCLASS_t {};
static constexpr auto qt_meta_stringdata_CLASSIntegerDialWidgetENDCLASS = QtMocHelpers::stringData(
    "IntegerDialWidget",
    "value",
    "Maximum",
    "Minimum",
    "Starting_Angle"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSIntegerDialWidgetENDCLASS_t {
    uint offsetsAndSizes[10];
    char stringdata0[18];
    char stringdata1[6];
    char stringdata2[8];
    char stringdata3[8];
    char stringdata4[15];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSIntegerDialWidgetENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSIntegerDialWidgetENDCLASS_t qt_meta_stringdata_CLASSIntegerDialWidgetENDCLASS = {
    {
        QT_MOC_LITERAL(0, 17),  // "IntegerDialWidget"
        QT_MOC_LITERAL(18, 5),  // "value"
        QT_MOC_LITERAL(24, 7),  // "Maximum"
        QT_MOC_LITERAL(32, 7),  // "Minimum"
        QT_MOC_LITERAL(40, 14)   // "Starting_Angle"
    },
    "IntegerDialWidget",
    "value",
    "Maximum",
    "Minimum",
    "Starting_Angle"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSIntegerDialWidgetENDCLASS[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       4,   14, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // properties: name, type, flags
       1, QMetaType::Int, 0x00015003, uint(-1), 0,
       2, QMetaType::Int, 0x01015003, uint(-1), 0,
       3, QMetaType::Int, 0x01015003, uint(-1), 0,
       4, QMetaType::Double, 0x01015003, uint(-1), 0,

       0        // eod
};

Q_CONSTINIT const QMetaObject IntegerDialWidget::staticMetaObject = { {
    QMetaObject::SuperData::link<IntegerDisplayWidget::staticMetaObject>(),
    qt_meta_stringdata_CLASSIntegerDialWidgetENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSIntegerDialWidgetENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSIntegerDialWidgetENDCLASS_t,
        // property 'value'
        QtPrivate::TypeAndForceComplete<int, std::true_type>,
        // property 'Maximum'
        QtPrivate::TypeAndForceComplete<int, std::true_type>,
        // property 'Minimum'
        QtPrivate::TypeAndForceComplete<int, std::true_type>,
        // property 'Starting_Angle'
        QtPrivate::TypeAndForceComplete<double, std::true_type>,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<IntegerDialWidget, std::true_type>
    >,
    nullptr
} };

void IntegerDialWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<IntegerDialWidget *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< int*>(_v) = _t->m_value; break;
        case 1: *reinterpret_cast< int*>(_v) = _t->max(); break;
        case 2: *reinterpret_cast< int*>(_v) = _t->min(); break;
        case 3: *reinterpret_cast< double*>(_v) = _t->startingAngle(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<IntegerDialWidget *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0:
            if (_t->m_value != *reinterpret_cast< int*>(_v)) {
                _t->m_value = *reinterpret_cast< int*>(_v);
            }
            break;
        case 1: _t->setMax(*reinterpret_cast< int*>(_v)); break;
        case 2: _t->setMin(*reinterpret_cast< int*>(_v)); break;
        case 3: _t->setStartingAngle(*reinterpret_cast< double*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    } else if (_c == QMetaObject::BindableProperty) {
    }
    (void)_o;
    (void)_id;
    (void)_c;
    (void)_a;
}

const QMetaObject *IntegerDialWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *IntegerDialWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSIntegerDialWidgetENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return IntegerDisplayWidget::qt_metacast(_clname);
}

int IntegerDialWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = IntegerDisplayWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}
QT_WARNING_POP
