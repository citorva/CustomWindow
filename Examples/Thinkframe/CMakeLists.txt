cmake_minimum_required(VERSION 3.6)
project(CustomWindow-thinkframe-example

include_directories(${CMAKE_SOURCE_DIR})
include_directories(${CMAKE_SOURCE_DIR}/../../CustomWindow)

if(WIN32 AND CMAKE_SIZEOF_VOID_P EQUAL 8)
    # 64bit
    set (CMAKE_PREFIX_PATH "D:\\Qt\\5.11.1\\msvc2017_64\\")
elseif(WIN32)
    set (CMAKE_PREFIX_PATH "D:\\Qt\\5.11.1\\msvc2015\\")
endif()

set(
    SOURCE_FILES
    main.cc 
    ../../CustomWindow/CustomWindow.cc
    ../../CustomWindow/CustomWindow.hh
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt5Widgets 5.8 REQUIRED)

if (WIN32)
    add_executable(CustomWindow-thinkframe-example WIN32 ${SOURCE_FILES} ${QRC_FILES})

    # deploy
    get_target_property(QT5_QMAKE_EXECUTABLE Qt5::qmake IMPORTED_LOCATION)
    set(EXAMPLE_LIBS Qt5::Widgets dwmapi uxtheme)

    add_custom_command(
        TARGET CustomWindow-example POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
            $<TARGET_FILE:Qt5::Widgets>
            $<TARGET_FILE_DIR:CustomWindow-example>
    )
    add_custom_command(
        TARGET CustomWindow-example POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
            $<TARGET_FILE:Qt5::Core>
            $<TARGET_FILE_DIR:CustomWindow-example>
    )
    add_custom_command(
        TARGET CustomWindow-example POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
            $<TARGET_FILE:Qt5::Gui>
            $<TARGET_FILE_DIR:CustomWindow-example>
    )

else()
    set(EXAMPLE_LIBS Qt5::Widgets)
endif()

target_link_libraries(CustomWindow-thinkframe-example LINK_PUBLIC ${EXAMPLE_LIBS})