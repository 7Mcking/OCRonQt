cmake_minimum_required(VERSION 3.27)
project(OCR)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)




find_package(Qt5 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)


find_package(OpenCV REQUIRED)
find_package(PkgConfig REQUIRED)

pkg_check_modules(Tesseract REQUIRED tesseract)

include_directories(${Tesseract_INCLUDE_DIRS})
add_definitions(-DTESSDATA_PREFIX=\"/opt/homebrew/share/tessdata/\")
include_directories("/System/Library/Frameworks/OpenGL.framework/Headers;/System/Library/Frameworks/AGL.framework/Headers")
add_executable(OCR main.cpp
        MainWindow.h
        MainWindow.cpp
        ScreenCaptureClass/ScreenCapture.h
        ScreenCaptureClass/ScreenCapture.cpp)
target_link_libraries(OCR
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
        ${OpenCV_LIBS}
        /opt/homebrew/lib/libtesseract.dylib
)
