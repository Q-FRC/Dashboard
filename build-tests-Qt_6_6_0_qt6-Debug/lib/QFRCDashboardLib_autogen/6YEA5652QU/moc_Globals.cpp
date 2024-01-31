/****************************************************************************
** Meta object code from reading C++ file 'Globals.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.6.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../lib/include/Globals.h"
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Globals.h' doesn't include <QObject>."
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
struct qt_meta_stringdata_CLASSGlobalsENDCLASS_t {};
static constexpr auto qt_meta_stringdata_CLASSGlobalsENDCLASS = QtMocHelpers::stringData(
    "Globals",
    "FrameShape",
    "Circle",
    "Triangle",
    "Rectangle",
    "Hexagon"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSGlobalsENDCLASS_t {
    uint offsetsAndSizes[12];
    char stringdata0[8];
    char stringdata1[11];
    char stringdata2[7];
    char stringdata3[9];
    char stringdata4[10];
    char stringdata5[8];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSGlobalsENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSGlobalsENDCLASS_t qt_meta_stringdata_CLASSGlobalsENDCLASS = {
    {
        QT_MOC_LITERAL(0, 7),  // "Globals"
        QT_MOC_LITERAL(8, 10),  // "FrameShape"
        QT_MOC_LITERAL(19, 6),  // "Circle"
        QT_MOC_LITERAL(26, 8),  // "Triangle"
        QT_MOC_LITERAL(35, 9),  // "Rectangle"
        QT_MOC_LITERAL(45, 7)   // "Hexagon"
    },
    "Globals",
    "FrameShape",
    "Circle",
    "Triangle",
    "Rectangle",
    "Hexagon"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSGlobalsENDCLASS[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       1,   14, // enums/sets
       0,    0, // constructors
       4,       // flags
       0,       // signalCount

 // enums: name, alias, flags, count, data
       1,    1, 0x2,    4,   19,

 // enum data: key, value
       2, uint(Globals::FrameShape::Circle),
       3, uint(Globals::FrameShape::Triangle),
       4, uint(Globals::FrameShape::Rectangle),
       5, uint(Globals::FrameShape::Hexagon),

       0        // eod
};

Q_CONSTINIT const QMetaObject Globals::staticMetaObject = { {
    nullptr,
    qt_meta_stringdata_CLASSGlobalsENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSGlobalsENDCLASS,
    nullptr,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSGlobalsENDCLASS_t,
        // enum 'FrameShape'
        QtPrivate::TypeAndForceComplete<Globals::FrameShape, std::true_type>,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<void, std::true_type>
    >,
    nullptr
} };

QT_WARNING_POP
