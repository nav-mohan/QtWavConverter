cmake_minimum_required(VERSION 3.10)
project(qthread_wav2mp3 LANGUAGES CXX)
# the name of the target operating system
set(CMAKE_SYSTEM_NAME Darwin)
# which compilers to use for C and C++
# set(CMAKE_SYSTEM_PROCESSOR x86_64)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_PREFIX_PATH "/opt/homebrew/Cellar/qt@5/5.15.8_1")
set(QT_REQUIRED_PACKAGES Core Multimedia Gui Widgets PrintSupport)
find_package(Qt5 REQUIRED COMPONENTS ${QT_REQUIRED_PACKAGES})

set(CMAKE_INCLUDE_CURRENT_DIR ON)
qt_wrap_ui(UI_HEADERS mainwindow.ui)
set(CPP_SOURCE_FILES main.cpp mainwindow.cpp worker.cpp LameEncoder.cpp constants.h)

add_executable(${PROJECT_NAME} ${CPP_SOURCE_FILES} ${UI_HEADERS})

set(QT_LINK_LIBRARIES Qt5::Core Qt5::Gui Qt5::Multimedia Qt5::Widgets Qt5::PrintSupport)
set(LAME_LINK_LIBRARY /opt/homebrew/Cellar/lame/3.100/lib/libmp3lame.a)
target_include_directories(${PROJECT_NAME} PUBLIC /opt/homebrew/Cellar/lame/3.100/include)
target_link_libraries(${PROJECT_NAME} PUBLIC ${QT_LINK_LIBRARIES} ${LAME_LINK_LIBRARY})
