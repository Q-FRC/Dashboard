/****************************************************************************
** Meta object code from reading C++ file 'MainWindow.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.6.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../lib/include/MainWindow.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MainWindow.h' doesn't include <QObject>."
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
struct qt_meta_stringdata_CLASSMainWindowENDCLASS_t {};
static constexpr auto qt_meta_stringdata_CLASSMainWindowENDCLASS = QtMocHelpers::stringData(
    "MainWindow",
    "forceUpdateTab",
    "",
    "idx",
    "moveTab",
    "from",
    "to",
    "preferences",
    "ntSettingsPopup",
    "setNtSettings",
    "ServerData",
    "data",
    "save",
    "saveAs",
    "openDialog",
    "open",
    "QFile&",
    "file",
    "refreshRecentFiles",
    "addRecentFile",
    "newTab",
    "closeTab",
    "setMaxSize",
    "renameTab",
    "newWidgetPopup",
    "beginNewWidgetDrag",
    "BaseWidget*",
    "widget",
    "WidgetData",
    "newCameraView",
    "newGraph",
    "cameraServerPopup",
    "about",
    "aboutQt"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSMainWindowENDCLASS_t {
    uint offsetsAndSizes[68];
    char stringdata0[11];
    char stringdata1[15];
    char stringdata2[1];
    char stringdata3[4];
    char stringdata4[8];
    char stringdata5[5];
    char stringdata6[3];
    char stringdata7[12];
    char stringdata8[16];
    char stringdata9[14];
    char stringdata10[11];
    char stringdata11[5];
    char stringdata12[5];
    char stringdata13[7];
    char stringdata14[11];
    char stringdata15[5];
    char stringdata16[7];
    char stringdata17[5];
    char stringdata18[19];
    char stringdata19[14];
    char stringdata20[7];
    char stringdata21[9];
    char stringdata22[11];
    char stringdata23[10];
    char stringdata24[15];
    char stringdata25[19];
    char stringdata26[12];
    char stringdata27[7];
    char stringdata28[11];
    char stringdata29[14];
    char stringdata30[9];
    char stringdata31[18];
    char stringdata32[6];
    char stringdata33[8];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSMainWindowENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSMainWindowENDCLASS_t qt_meta_stringdata_CLASSMainWindowENDCLASS = {
    {
        QT_MOC_LITERAL(0, 10),  // "MainWindow"
        QT_MOC_LITERAL(11, 14),  // "forceUpdateTab"
        QT_MOC_LITERAL(26, 0),  // ""
        QT_MOC_LITERAL(27, 3),  // "idx"
        QT_MOC_LITERAL(31, 7),  // "moveTab"
        QT_MOC_LITERAL(39, 4),  // "from"
        QT_MOC_LITERAL(44, 2),  // "to"
        QT_MOC_LITERAL(47, 11),  // "preferences"
        QT_MOC_LITERAL(59, 15),  // "ntSettingsPopup"
        QT_MOC_LITERAL(75, 13),  // "setNtSettings"
        QT_MOC_LITERAL(89, 10),  // "ServerData"
        QT_MOC_LITERAL(100, 4),  // "data"
        QT_MOC_LITERAL(105, 4),  // "save"
        QT_MOC_LITERAL(110, 6),  // "saveAs"
        QT_MOC_LITERAL(117, 10),  // "openDialog"
        QT_MOC_LITERAL(128, 4),  // "open"
        QT_MOC_LITERAL(133, 6),  // "QFile&"
        QT_MOC_LITERAL(140, 4),  // "file"
        QT_MOC_LITERAL(145, 18),  // "refreshRecentFiles"
        QT_MOC_LITERAL(164, 13),  // "addRecentFile"
        QT_MOC_LITERAL(178, 6),  // "newTab"
        QT_MOC_LITERAL(185, 8),  // "closeTab"
        QT_MOC_LITERAL(194, 10),  // "setMaxSize"
        QT_MOC_LITERAL(205, 9),  // "renameTab"
        QT_MOC_LITERAL(215, 14),  // "newWidgetPopup"
        QT_MOC_LITERAL(230, 18),  // "beginNewWidgetDrag"
        QT_MOC_LITERAL(249, 11),  // "BaseWidget*"
        QT_MOC_LITERAL(261, 6),  // "widget"
        QT_MOC_LITERAL(268, 10),  // "WidgetData"
        QT_MOC_LITERAL(279, 13),  // "newCameraView"
        QT_MOC_LITERAL(293, 8),  // "newGraph"
        QT_MOC_LITERAL(302, 17),  // "cameraServerPopup"
        QT_MOC_LITERAL(320, 5),  // "about"
        QT_MOC_LITERAL(326, 7)   // "aboutQt"
    },
    "MainWindow",
    "forceUpdateTab",
    "",
    "idx",
    "moveTab",
    "from",
    "to",
    "preferences",
    "ntSettingsPopup",
    "setNtSettings",
    "ServerData",
    "data",
    "save",
    "saveAs",
    "openDialog",
    "open",
    "QFile&",
    "file",
    "refreshRecentFiles",
    "addRecentFile",
    "newTab",
    "closeTab",
    "setMaxSize",
    "renameTab",
    "newWidgetPopup",
    "beginNewWidgetDrag",
    "BaseWidget*",
    "widget",
    "WidgetData",
    "newCameraView",
    "newGraph",
    "cameraServerPopup",
    "about",
    "aboutQt"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSMainWindowENDCLASS[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
      22,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,  146,    2, 0x0a,    1 /* Public */,
       4,    2,  149,    2, 0x0a,    3 /* Public */,
       7,    0,  154,    2, 0x0a,    6 /* Public */,
       8,    0,  155,    2, 0x0a,    7 /* Public */,
       9,    1,  156,    2, 0x0a,    8 /* Public */,
      12,    0,  159,    2, 0x0a,   10 /* Public */,
      13,    0,  160,    2, 0x0a,   11 /* Public */,
      14,    0,  161,    2, 0x0a,   12 /* Public */,
      15,    1,  162,    2, 0x0a,   13 /* Public */,
      18,    0,  165,    2, 0x0a,   15 /* Public */,
      19,    1,  166,    2, 0x0a,   16 /* Public */,
      20,    0,  169,    2, 0x0a,   18 /* Public */,
      21,    0,  170,    2, 0x0a,   19 /* Public */,
      22,    0,  171,    2, 0x0a,   20 /* Public */,
      23,    0,  172,    2, 0x0a,   21 /* Public */,
      24,    0,  173,    2, 0x0a,   22 /* Public */,
      25,    2,  174,    2, 0x0a,   23 /* Public */,
      29,    0,  179,    2, 0x0a,   26 /* Public */,
      30,    0,  180,    2, 0x0a,   27 /* Public */,
      31,    0,  181,    2, 0x0a,   28 /* Public */,
      32,    0,  182,    2, 0x0a,   29 /* Public */,
      33,    0,  183,    2, 0x0a,   30 /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    5,    6,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 10,   11,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 16,   17,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 16,   17,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 26, 0x80000000 | 28,   27,   11,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject MainWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_CLASSMainWindowENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSMainWindowENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSMainWindowENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<MainWindow, std::true_type>,
        // method 'forceUpdateTab'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'moveTab'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'preferences'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'ntSettingsPopup'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'setNtSettings'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<ServerData, std::false_type>,
        // method 'save'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'saveAs'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'openDialog'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'open'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QFile &, std::false_type>,
        // method 'refreshRecentFiles'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'addRecentFile'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QFile &, std::false_type>,
        // method 'newTab'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'closeTab'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'setMaxSize'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'renameTab'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'newWidgetPopup'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'beginNewWidgetDrag'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<BaseWidget *, std::false_type>,
        QtPrivate::TypeAndForceComplete<WidgetData, std::false_type>,
        // method 'newCameraView'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'newGraph'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'cameraServerPopup'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'about'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'aboutQt'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainWindow *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->forceUpdateTab((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 1: _t->moveTab((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2]))); break;
        case 2: _t->preferences(); break;
        case 3: _t->ntSettingsPopup(); break;
        case 4: _t->setNtSettings((*reinterpret_cast< std::add_pointer_t<ServerData>>(_a[1]))); break;
        case 5: _t->save(); break;
        case 6: _t->saveAs(); break;
        case 7: _t->openDialog(); break;
        case 8: _t->open((*reinterpret_cast< std::add_pointer_t<QFile&>>(_a[1]))); break;
        case 9: _t->refreshRecentFiles(); break;
        case 10: _t->addRecentFile((*reinterpret_cast< std::add_pointer_t<QFile&>>(_a[1]))); break;
        case 11: _t->newTab(); break;
        case 12: _t->closeTab(); break;
        case 13: _t->setMaxSize(); break;
        case 14: _t->renameTab(); break;
        case 15: _t->newWidgetPopup(); break;
        case 16: _t->beginNewWidgetDrag((*reinterpret_cast< std::add_pointer_t<BaseWidget*>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<WidgetData>>(_a[2]))); break;
        case 17: _t->newCameraView(); break;
        case 18: _t->newGraph(); break;
        case 19: _t->cameraServerPopup(); break;
        case 20: _t->about(); break;
        case 21: _t->aboutQt(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
        case 16:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< BaseWidget* >(); break;
            }
            break;
        }
    }
}

const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSMainWindowENDCLASS.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "Ui::MainWindow"))
        return static_cast< Ui::MainWindow*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 22)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 22;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 22)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 22;
    }
    return _id;
}
QT_WARNING_POP
