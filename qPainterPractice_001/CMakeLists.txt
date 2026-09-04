cmake_minimum_required(VERSION 3.19)
project(qPainterPractice_001 LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Gui)

qt_standard_project_setup()

qt_add_executable(qPainterPractice_001
    main.cpp
    mrpainter.hpp mrpainter.cpp
)

target_link_libraries(qPainterPractice_001
    PRIVATE
        Qt::Gui
)

install(TARGETS qPainterPractice_001
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)
