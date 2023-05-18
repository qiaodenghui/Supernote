cmake_minimum_required(VERSION 3.16)

project(Supernote VERSION 0.1 LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(app_icon_resource_windows "${CMAKE_CURRENT_SOURCE_DIR}/resource/supernote.rc")

find_package(Qt6 6.2 REQUIRED COMPONENTS Quick Network)

qt_standard_project_setup()

#指定库的路径
link_directories(CMAKE_CURRENT_SOURCE_DIR
    ./library/Myscript/lib/win-x64/
    ./library/Note/lib/
    ./library/Docx/lib/
)

#指定库的头文件路径
set(IINK_INCLUDES   ./library/Myscript/include)
set(Note_INCLUDES ./library/Note/include)
set(Docx_INCLUDES ./library/Docx/include)

set(include_files
    ./include/utils.h
    ./include/export.h
    ./include/FontMetricsProvider.h
    ./include/noteview.h
    ./include/noteinfo.h
    ./include/MyCertificate.h
    ./include/RendererListener.h
    ./include/EditorListener.h
)
set(src_files
    ./src/utils.cpp
    ./src/export.cpp
    ./src/FontMetricsProvider.cpp
    ./src/noteview.cpp
    ./src/noteinfo.cpp
    ./src/main.cpp
)
include_directories(
    ./include
)

set(qml_files
    ./layout/main.qml
    ./layout/FirstView.qml
    ./layout/SecondView.qml
    ./layout/NoteWindow.qml
    ./layout/FooterView.qml
    ./layout/HeaderView.qml
    ./layout/NoteMenuBar.qml
    ./layout/ExportView.qml
    ./layout/LangModel.qml
    ./layout/ExportSetting.qml
)

set(qml_resource_files
    ./images/logo.png
    ./images/arrow_left.png
    ./images/arrow_right.png
    ./images/double_arrow_left.png
    ./images/double_arrow_right.png
)

qt_add_executable(Supernote
    ${app_icon_resource_windows}
    ${include_files}
    ${src_files}
)

#这里添加可以在C++中使用
qt_add_resources(Supernote "doc"
    PREFIX
    "/"
    FILES
    doc/new_docx.docx
    images/sn_icon.png
)

qt_add_qml_module(Supernote
    URI Supernote
    VERSION 1.0
    QML_FILES ${qml_files}
    RESOURCES ${qml_resource_files}
)

#注意放置位置，靠前会报错要在qt_add_executable之后
target_include_directories(Supernote
    PRIVATE
    ${Docx_INCLUDES}
    ${Note_INCLUDES}
    ${IINK_INCLUDES}
)

set_target_properties(Supernote PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(Supernote
    PRIVATE Qt6::Quick
    PRIVATE Qt6::Network
    PRIVATE Note
    PRIVATE Docx
    PRIVATE iink
)

install(TARGETS Supernote
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
