/****************************************************************************
** Meta object code from reading C++ file 'BooleanDisplayWidget.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.6.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../lib/include/widgets/BooleanDisplayWidget.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'BooleanDisplayWidget.h' doesn't include <QObject>."
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
struct qt_meta_stringdata_CLASSBooleanDisplayWidgetENDCLASS_t {};
static constexpr auto qt_meta_stringdata_CLASSBooleanDisplayWidgetENDCLASS = QtMocHelpers::stringData(
    "BooleanDisplayWidget",
    "value",
    "True_Color",
    "False_Color",
    "Shape",
    "Globals::FrameShape"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSBooleanDisplayWidgetENDCLASS_t {
    uint offsetsAndSizes[12];
    char stringdata0[21];
    char stringdata1[6];
    char stringdata2[11];
    char stringdata3[12];
    char stringdata4[6];
    char stringdata5[20];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSBooleanDisplayWidgetENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSBooleanDisplayWidgetENDCLASS_t qt_meta_stringdata_CLASSBooleanDisplayWidgetENDCLASS = {
    {
        QT_MOC_LITERAL(0, 20),  // "BooleanDisplayWidget"
        QT_MOC_LITERAL(21, 5),  // "value"
        QT_MOC_LITERAL(27, 10),  // "True_Color"
        QT_MOC_LITERAL(38, 11),  // "False_Color"
        QT_MOC_LITERAL(50, 5),  // "Shape"
        QT_MOC_LITERAL(56, 19)   // "Globals::FrameShape"
    },
    "BooleanDisplayWidget",
    "value",
    "True_Color",
    "False_Color",
    "Shape",
    "Globals::FrameShape"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSBooleanDisplayWidgetENDCLASS[] = {

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
       1, QMetaType::Bool, 0x00015003, uint(-1), 0,
       2, QMetaType::QColor, 0x01015003, uint(-1), 0,
       3, QMetaType::QColor, 0x01015003, uint(-1), 0,
       4, 0x80000000 | 5, 0x0101510b, uint(-1), 0,

       0        // eod
};

Q_CONSTINIT static const QMetaObject::SuperData qt_meta_extradata_CLASSBooleanDisplayWidgetENDCLASS[] = {
    QMetaObject::SuperData::link<Globals::staticMetaObject>(),
    nullptr
};

Q_CONSTINIT const QMetaObject BooleanDisplayWidget::staticMetaObject = { {
    QMetaObject::SuperData::link<BaseWidget::staticMetaObject>(),
    qt_meta_stringdata_CLASSBooleanDisplayWidgetENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSBooleanDisplayWidgetENDCLASS,
    qt_static_metacall,
    qt_meta_extradata_CLASSBooleanDisplayWidgetENDCLASS,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSBooleanDisplayWidgetENDCLASS_t,
        // property 'value'
        QtPrivate::TypeAndForceComplete<bool, std::true_type>,
        // property 'True_Color'
        QtPrivate::TypeAndForceComplete<QColor, std::true_type>,
        // property 'False_Color'
        QtPrivate::TypeAndForceComplete<QColor, std::true_type>,
        // property 'Shape'
        QtPrivate::TypeAndForceComplete<Globals::FrameShape, std::true_type>,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<BooleanDisplayWidget, std::true_type>
    >,
    nullptr
} };

void BooleanDisplayWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<BooleanDisplayWidget *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< bool*>(_v) = _t->m_value; break;
        case 1: *reinterpret_cast< QColor*>(_v) = _t->trueColor(); break;
        case 2: *reinterpret_cast< QColor*>(_v) = _t->falseColor(); break;
        case 3: *reinterpret_cast< Globals::FrameShape*>(_v) = _t->shape(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<BooleanDisplayWidget *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0:
            if (_t->m_value != *reinterpret_cast< bool*>(_v)) {
                _t->m_value = *reinterpret_cast< bool*>(_v);
            }
            break;
        case 1: _t->setTrueColor(*reinterpret_cast< QColor*>(_v)); break;
        case 2: _t->setFalseColor(*reinterpret_cast< QColor*>(_v)); break;
        case 3: _t->setShape(*reinterpret_cast< Globals::FrameShape*>(_v)); break;
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

const QMetaObject *BooleanDisplayWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *BooleanDisplayWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSBooleanDisplayWidgetENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return BaseWidget::qt_metacast(_clname);
}

int BooleanDisplayWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = BaseWidget::qt_metacall(_c, _id, _a);
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
