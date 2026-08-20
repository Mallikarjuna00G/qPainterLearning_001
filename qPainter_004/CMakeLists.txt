cmake_minimum_required(VERSION 3.19)
project(qPainter_004 LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets)

qt_standard_project_setup()

qt_add_executable(qPainter_004
    WIN32 MACOSX_BUNDLE
    main.cpp
    canvaswidget.cpp
    canvaswidget.hpp
)

target_link_libraries(qPainter_004
    PRIVATE
        Qt::Core
        Qt::Widgets
)

install(TARGETS qPainter_004
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET qPainter_004
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
