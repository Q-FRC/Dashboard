/****************************************************************************
** Meta object code from reading C++ file 'EnumWidget.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.6.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../lib/include/widgets/EnumWidget.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'EnumWidget.h' doesn't include <QObject>."
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
struct qt_meta_stringdata_CLASSEnumWidgetENDCLASS_t {};
static constexpr auto qt_meta_stringdata_CLASSEnumWidgetENDCLASS = QtMocHelpers::stringData(
    "EnumWidget",
    "value",
    "Colors",
    "Shape",
    "Globals::FrameShape"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSEnumWidgetENDCLASS_t {
    uint offsetsAndSizes[10];
    char stringdata0[11];
    char stringdata1[6];
    char stringdata2[7];
    char stringdata3[6];
    char stringdata4[20];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSEnumWidgetENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSEnumWidgetENDCLASS_t qt_meta_stringdata_CLASSEnumWidgetENDCLASS = {
    {
        QT_MOC_LITERAL(0, 10),  // "EnumWidget"
        QT_MOC_LITERAL(11, 5),  // "value"
        QT_MOC_LITERAL(17, 6),  // "Colors"
        QT_MOC_LITERAL(24, 5),  // "Shape"
        QT_MOC_LITERAL(30, 19)   // "Globals::FrameShape"
    },
    "EnumWidget",
    "value",
    "Colors",
    "Shape",
    "Globals::FrameShape"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSEnumWidgetENDCLASS[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       3,   14, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // properties: name, type, flags
       1, QMetaType::QString, 0x00015003, uint(-1), 0,
       2, QMetaType::QVariantMap, 0x01015103, uint(-1), 0,
       3, 0x80000000 | 4, 0x0101510b, uint(-1), 0,

       0        // eod
};

Q_CONSTINIT static const QMetaObject::SuperData qt_meta_extradata_CLASSEnumWidgetENDCLASS[] = {
    QMetaObject::SuperData::link<Globals::staticMetaObject>(),
    nullptr
};

Q_CONSTINIT const QMetaObject EnumWidget::staticMetaObject = { {
    QMetaObject::SuperData::link<BaseWidget::staticMetaObject>(),
    qt_meta_stringdata_CLASSEnumWidgetENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSEnumWidgetENDCLASS,
    qt_static_metacall,
    qt_meta_extradata_CLASSEnumWidgetENDCLASS,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSEnumWidgetENDCLASS_t,
        // property 'value'
        QtPrivate::TypeAndForceComplete<QString, std::true_type>,
        // property 'Colors'
        QtPrivate::TypeAndForceComplete<QVariantMap, std::true_type>,
        // property 'Shape'
        QtPrivate::TypeAndForceComplete<Globals::FrameShape, std::true_type>,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<EnumWidget, std::true_type>
    >,
    nullptr
} };

void EnumWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<EnumWidget *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QString*>(_v) = _t->m_value; break;
        case 1: *reinterpret_cast< QVariantMap*>(_v) = _t->colors(); break;
        case 2: *reinterpret_cast< Globals::FrameShape*>(_v) = _t->shape(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<EnumWidget *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0:
            if (_t->m_value != *reinterpret_cast< QString*>(_v)) {
                _t->m_value = *reinterpret_cast< QString*>(_v);
            }
            break;
        case 1: _t->setColors(*reinterpret_cast< QVariantMap*>(_v)); break;
        case 2: _t->setShape(*reinterpret_cast< Globals::FrameShape*>(_v)); break;
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

const QMetaObject *EnumWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *EnumWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSEnumWidgetENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return BaseWidget::qt_metacast(_clname);
}

int EnumWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = BaseWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}
QT_WARNING_POP
