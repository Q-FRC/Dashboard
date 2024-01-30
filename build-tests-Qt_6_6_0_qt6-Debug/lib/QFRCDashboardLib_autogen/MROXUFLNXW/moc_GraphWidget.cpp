/****************************************************************************
** Meta object code from reading C++ file 'GraphWidget.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.6.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../lib/include/widgets/GraphWidget.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'GraphWidget.h' doesn't include <QObject>."
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
struct qt_meta_stringdata_CLASSGraphWidgetENDCLASS_t {};
static constexpr auto qt_meta_stringdata_CLASSGraphWidgetENDCLASS = QtMocHelpers::stringData(
    "GraphWidget",
    "updateGraph",
    "",
    "exportCSVPopup",
    "exportCSV",
    "fileName",
    "Topics",
    "QHash<Globals::Topic,QColor>",
    "Update_Frequency_Seconds",
    "Time_Scale_Seconds",
    "Max_Y_Value",
    "Min_Y_Value",
    "X_Axis_Topic",
    "Globals::GraphXAxis"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSGraphWidgetENDCLASS_t {
    uint offsetsAndSizes[28];
    char stringdata0[12];
    char stringdata1[12];
    char stringdata2[1];
    char stringdata3[15];
    char stringdata4[10];
    char stringdata5[9];
    char stringdata6[7];
    char stringdata7[29];
    char stringdata8[25];
    char stringdata9[19];
    char stringdata10[12];
    char stringdata11[12];
    char stringdata12[13];
    char stringdata13[20];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSGraphWidgetENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSGraphWidgetENDCLASS_t qt_meta_stringdata_CLASSGraphWidgetENDCLASS = {
    {
        QT_MOC_LITERAL(0, 11),  // "GraphWidget"
        QT_MOC_LITERAL(12, 11),  // "updateGraph"
        QT_MOC_LITERAL(24, 0),  // ""
        QT_MOC_LITERAL(25, 14),  // "exportCSVPopup"
        QT_MOC_LITERAL(40, 9),  // "exportCSV"
        QT_MOC_LITERAL(50, 8),  // "fileName"
        QT_MOC_LITERAL(59, 6),  // "Topics"
        QT_MOC_LITERAL(66, 28),  // "QHash<Globals::Topic,QColor>"
        QT_MOC_LITERAL(95, 24),  // "Update_Frequency_Seconds"
        QT_MOC_LITERAL(120, 18),  // "Time_Scale_Seconds"
        QT_MOC_LITERAL(139, 11),  // "Max_Y_Value"
        QT_MOC_LITERAL(151, 11),  // "Min_Y_Value"
        QT_MOC_LITERAL(163, 12),  // "X_Axis_Topic"
        QT_MOC_LITERAL(176, 19)   // "Globals::GraphXAxis"
    },
    "GraphWidget",
    "updateGraph",
    "",
    "exportCSVPopup",
    "exportCSV",
    "fileName",
    "Topics",
    "QHash<Globals::Topic,QColor>",
    "Update_Frequency_Seconds",
    "Time_Scale_Seconds",
    "Max_Y_Value",
    "Min_Y_Value",
    "X_Axis_Topic",
    "Globals::GraphXAxis"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSGraphWidgetENDCLASS[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       6,   37, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   32,    2, 0x0a,    7 /* Public */,
       3,    0,   33,    2, 0x0a,    8 /* Public */,
       4,    1,   34,    2, 0x0a,    9 /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    5,

 // properties: name, type, flags
       6, 0x80000000 | 7, 0x0101510b, uint(-1), 0,
       8, QMetaType::Double, 0x01015003, uint(-1), 0,
       9, QMetaType::Double, 0x01015003, uint(-1), 0,
      10, QMetaType::Double, 0x01015003, uint(-1), 0,
      11, QMetaType::Double, 0x01015003, uint(-1), 0,
      12, 0x80000000 | 13, 0x0101500b, uint(-1), 0,

       0        // eod
};

Q_CONSTINIT static const QMetaObject::SuperData qt_meta_extradata_CLASSGraphWidgetENDCLASS[] = {
    QMetaObject::SuperData::link<Globals::staticMetaObject>(),
    nullptr
};

Q_CONSTINIT const QMetaObject GraphWidget::staticMetaObject = { {
    QMetaObject::SuperData::link<BaseWidget::staticMetaObject>(),
    qt_meta_stringdata_CLASSGraphWidgetENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSGraphWidgetENDCLASS,
    qt_static_metacall,
    qt_meta_extradata_CLASSGraphWidgetENDCLASS,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSGraphWidgetENDCLASS_t,
        // property 'Topics'
        QtPrivate::TypeAndForceComplete<QHash<Globals::Topic,QColor>, std::true_type>,
        // property 'Update_Frequency_Seconds'
        QtPrivate::TypeAndForceComplete<double, std::true_type>,
        // property 'Time_Scale_Seconds'
        QtPrivate::TypeAndForceComplete<double, std::true_type>,
        // property 'Max_Y_Value'
        QtPrivate::TypeAndForceComplete<double, std::true_type>,
        // property 'Min_Y_Value'
        QtPrivate::TypeAndForceComplete<double, std::true_type>,
        // property 'X_Axis_Topic'
        QtPrivate::TypeAndForceComplete<Globals::GraphXAxis, std::true_type>,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<GraphWidget, std::true_type>,
        // method 'updateGraph'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'exportCSVPopup'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'exportCSV'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>
    >,
    nullptr
} };

void GraphWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<GraphWidget *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->updateGraph(); break;
        case 1: _t->exportCSVPopup(); break;
        case 2: _t->exportCSV((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterPropertyMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 5:
            *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< Globals::GraphXAxis >(); break;
        }
    }  else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<GraphWidget *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QHash<Globals::Topic,QColor>*>(_v) = _t->topics(); break;
        case 1: *reinterpret_cast< double*>(_v) = _t->updateFrequency(); break;
        case 2: *reinterpret_cast< double*>(_v) = _t->maxTimeScale(); break;
        case 3: *reinterpret_cast< double*>(_v) = _t->maxYValue(); break;
        case 4: *reinterpret_cast< double*>(_v) = _t->minYValue(); break;
        case 5: *reinterpret_cast< Globals::GraphXAxis*>(_v) = _t->xAxisData(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<GraphWidget *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setTopics(*reinterpret_cast< QHash<Globals::Topic,QColor>*>(_v)); break;
        case 1: _t->setUpdateFrequency(*reinterpret_cast< double*>(_v)); break;
        case 2: _t->setMaxTimeScale(*reinterpret_cast< double*>(_v)); break;
        case 3: _t->setMaxYValue(*reinterpret_cast< double*>(_v)); break;
        case 4: _t->setMinYValue(*reinterpret_cast< double*>(_v)); break;
        case 5: _t->setXAxisData(*reinterpret_cast< Globals::GraphXAxis*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    } else if (_c == QMetaObject::BindableProperty) {
    }
}

const QMetaObject *GraphWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *GraphWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSGraphWidgetENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return BaseWidget::qt_metacast(_clname);
}

int GraphWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = BaseWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 3;
    }else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    }
    return _id;
}
QT_WARNING_POP
