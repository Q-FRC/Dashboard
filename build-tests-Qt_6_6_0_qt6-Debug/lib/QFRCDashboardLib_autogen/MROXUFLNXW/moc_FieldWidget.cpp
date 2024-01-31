/****************************************************************************
** Meta object code from reading C++ file 'FieldWidget.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.6.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../lib/include/widgets/FieldWidget.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'FieldWidget.h' doesn't include <QObject>."
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
struct qt_meta_stringdata_CLASSFieldWidgetENDCLASS_t {};
static constexpr auto qt_meta_stringdata_CLASSFieldWidgetENDCLASS = QtMocHelpers::stringData(
    "FieldWidget",
    "value",
    "Image",
    "Globals::File",
    "Robot_Width",
    "Robot_Length"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSFieldWidgetENDCLASS_t {
    uint offsetsAndSizes[12];
    char stringdata0[12];
    char stringdata1[6];
    char stringdata2[6];
    char stringdata3[14];
    char stringdata4[12];
    char stringdata5[13];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSFieldWidgetENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSFieldWidgetENDCLASS_t qt_meta_stringdata_CLASSFieldWidgetENDCLASS = {
    {
        QT_MOC_LITERAL(0, 11),  // "FieldWidget"
        QT_MOC_LITERAL(12, 5),  // "value"
        QT_MOC_LITERAL(18, 5),  // "Image"
        QT_MOC_LITERAL(24, 13),  // "Globals::File"
        QT_MOC_LITERAL(38, 11),  // "Robot_Width"
        QT_MOC_LITERAL(50, 12)   // "Robot_Length"
    },
    "FieldWidget",
    "value",
    "Image",
    "Globals::File",
    "Robot_Width",
    "Robot_Length"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSFieldWidgetENDCLASS[] = {

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
       1, QMetaType::QVariantList, 0x00015003, uint(-1), 0,
       2, 0x80000000 | 3, 0x0101510b, uint(-1), 0,
       4, QMetaType::Double, 0x01015003, uint(-1), 0,
       5, QMetaType::Double, 0x01015003, uint(-1), 0,

       0        // eod
};

Q_CONSTINIT static const QMetaObject::SuperData qt_meta_extradata_CLASSFieldWidgetENDCLASS[] = {
    QMetaObject::SuperData::link<Globals::staticMetaObject>(),
    nullptr
};

Q_CONSTINIT const QMetaObject FieldWidget::staticMetaObject = { {
    QMetaObject::SuperData::link<BaseWidget::staticMetaObject>(),
    qt_meta_stringdata_CLASSFieldWidgetENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSFieldWidgetENDCLASS,
    qt_static_metacall,
    qt_meta_extradata_CLASSFieldWidgetENDCLASS,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSFieldWidgetENDCLASS_t,
        // property 'value'
        QtPrivate::TypeAndForceComplete<QVariantList, std::true_type>,
        // property 'Image'
        QtPrivate::TypeAndForceComplete<Globals::File, std::true_type>,
        // property 'Robot_Width'
        QtPrivate::TypeAndForceComplete<double, std::true_type>,
        // property 'Robot_Length'
        QtPrivate::TypeAndForceComplete<double, std::true_type>,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<FieldWidget, std::true_type>
    >,
    nullptr
} };

void FieldWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::RegisterPropertyMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 1:
            *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< Globals::File >(); break;
        }
    }  else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<FieldWidget *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QVariantList*>(_v) = _t->m_value; break;
        case 1: *reinterpret_cast< Globals::File*>(_v) = _t->image(); break;
        case 2: *reinterpret_cast< double*>(_v) = _t->robotWidth(); break;
        case 3: *reinterpret_cast< double*>(_v) = _t->robotLength(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<FieldWidget *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0:
            if (_t->m_value != *reinterpret_cast< QVariantList*>(_v)) {
                _t->m_value = *reinterpret_cast< QVariantList*>(_v);
            }
            break;
        case 1: _t->setImage(*reinterpret_cast< Globals::File*>(_v)); break;
        case 2: _t->setRobotWidth(*reinterpret_cast< double*>(_v)); break;
        case 3: _t->setRobotLength(*reinterpret_cast< double*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    } else if (_c == QMetaObject::BindableProperty) {
    }
    (void)_o;
}

const QMetaObject *FieldWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *FieldWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSFieldWidgetENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return BaseWidget::qt_metacast(_clname);
}

int FieldWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
