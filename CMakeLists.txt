cmake_minimum_required(VERSION 3.16)

set(Dashboard_APP_NAME QFRCDashboard)
set(Dashboard_EXEC_NAME Dashboard)

project(QFRCDashboard VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.5 REQUIRED COMPONENTS Quick)

qt_standard_project_setup(REQUIRES 6.5)

qt_add_executable(${Dashboard_EXEC_NAME}
    main.cpp
)

set_source_files_properties(Constants.qml
    PROPERTIES
    QT_QML_SINGLETON_TYPE true
)

qt_add_qml_module(${Dashboard_EXEC_NAME}
    URI QFRCDashboard
    VERSION 1.0
    QML_FILES Main.qml
    QML_FILES items/MainScreen.qml
    QML_FILES Constants.qml
    SOURCES include/models/TabWidgetsModel.h src/models/TabWidgetsModel.cpp
    QML_FILES widgets/TextWidget.qml
    QML_FILES items/Tab.qml
    SOURCES include/models/TabListModel.h src/models/TabListModel.cpp
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(${Dashboard_EXEC_NAME} PROPERTIES
    #    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.${Dashboard_EXEC_NAME}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(${Dashboard_EXEC_NAME}
    PRIVATE Qt6::Quick
)

target_include_directories(${Dashboard_EXEC_NAME} PRIVATE include/)
target_include_directories(${Dashboard_EXEC_NAME} PRIVATE include/models)

include(GNUInstallDirs)
install(TARGETS ${Dashboard_EXEC_NAME}
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
