cmake_minimum_required(VERSION 3.6)

set(PROJECT_NAME CustomWindow-loading-banner)
project(${PROJECT_NAME})

include_directories(${CMAKE_SOURCE_DIR})
include_directories(${CMAKE_SOURCE_DIR}/../../CustomWindow)

if(WIN32)
    #execute_process(COMMAND powershell -NoLogo -NonInteractive -File .\\getQtPath.ps1 WORKING_DIRECTORY ${CMAKE_SOURCE_DIR} OUTPUT_VARIABLE CMAKE_PREFIX_PATH)
    set (CMAKE_PREFIX_PATH "C:\\Qt\\5.11.2\\msvc2017_64\\")
    #message(${CMAKE_PREFIX_PATH})
endif()

set(
    SOURCE_FILES
    main.cc 
    ../../CustomWindow/CustomWindow.cc
    ../../CustomWindow/CustomWindow.hh
)

set(QRC_FILES data.qrc)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt5Widgets 5.8 REQUIRED)

if (WIN32)
    add_executable(${PROJECT_NAME} WIN32 ${SOURCE_FILES} ${QRC_FILES})
    set_property (DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})

    # deploy
    get_target_property(QT5_QMAKE_EXECUTABLE Qt5::qmake IMPORTED_LOCATION)
    set(EXAMPLE_LIBS Qt5::Widgets dwmapi uxtheme)

    add_custom_command(
        TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
            $<TARGET_FILE:Qt5::Widgets>
            $<TARGET_FILE_DIR:${PROJECT_NAME}>
    )
    add_custom_command(
        TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
            $<TARGET_FILE:Qt5::Core>
            $<TARGET_FILE_DIR:${PROJECT_NAME}>
    )
    add_custom_command(
        TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
            $<TARGET_FILE:Qt5::Gui>
            $<TARGET_FILE_DIR:${PROJECT_NAME}>
    )

else()
    set(EXAMPLE_LIBS Qt5::Widgets)
endif()

target_link_libraries(${PROJECT_NAME} LINK_PUBLIC ${EXAMPLE_LIBS})