
cmake_minimum_required(VERSION 3.0.0)
project(FacialRecognition VERSION 0.1.0)
set(CMAKE_AUTOMOC ON)
include(CTest)
enable_testing()
find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)
find_package(OpenCV REQUIRED)
find_package(dlib REQUIRED)



set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
)


add_executable(FacialRecognition ${PROJECT_SOURCES})
target_include_directories(FacialRecognition PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/headers)
target_link_libraries(FacialRecognition ${OpenCV_LIBS})
target_link_libraries(FacialRecognition Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(FacialRecognition dlib::dlib)
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
