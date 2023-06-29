cmake_minimum_required(VERSION 3.16)

project(Supernote VERSION 0.1 LANGUAGES CXX C)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(app_icon_resource_windows "${CMAKE_CURRENT_SOURCE_DIR}/resource/supernote.rc")

find_package(Qt6 6.2 REQUIRED COMPONENTS Quick Network LinguistTools)

#指定库的路径
link_directories(CMAKE_CURRENT_SOURCE_DIR
    ./library/Note/lib/
    ./library/Docx/lib/
)

if(WIN32)
    link_directories(CMAKE_CURRENT_SOURCE_DIR
       ./library/Myscript/lib/win-x64/
    )
#指定库的头文件路径
set(IINK_INCLUDES ./library/Myscript/include)

endif()


set(Note_INCLUDES ./library/Note/include)
set(Docx_INCLUDES ./library/Docx/include)

if(WIN32)
set(include_files
    ./include/Utils.h
    ./include/Export.h
    ./include/FontMetricsProvider.h
    ./include/NoteView.h
    ./include/NoteInfo.h
    ./include/Update.h
    ./include/Download.h
    ./include/VersionInfo.h
    ./include/GetVersion.h
    ./include/MyCertificate.h
    ./include/RendererListener.h
    ./include/EditorListener.h
    ./include/AppManager.h
)
set(src_files
    ./src/Utils.cpp
    ./src/Export.cpp
    ./src/FontMetricsProvider.cpp
    ./src/NoteView.cpp
    ./src/NoteInfo.cpp
    ./src/Update.cpp
    ./src/Download.cpp
    ./src/VersionInfo.cpp
    ./src/GetVersion.cpp
    ./src/Main.cpp
    ./src/AppManager.cpp

)
else()
    set(include_files
        ./include/Utils.h
        ./include/Export.h
        ./include/NoteView.h
        ./include/NoteInfo.h
        ./include/Update.h
        ./include/Download.h
        ./include/VersionInfo.h
        ./include/GetVersion.h
        ./include/AppManager.h
        ./include/MyCertificate.h
#        ./include/FontMetricsProvider.h
#        ./include/RendererListener.h
#        ./include/EditorListener.h
    )
set(src_files
    ./src/Utils.cpp
    ./src/Export.cpp
    ./src/NoteView.cpp
    ./src/NoteInfo.cpp
    ./src/Update.cpp
    ./src/Download.cpp
    ./src/VersionInfo.cpp
    ./src/GetVersion.cpp
    ./src/Main.cpp
    ./src/AppManager.cpp
#    ./src/FontMetricsProvider.cpp

)
endif()


include_directories(
    ./include
)

set(qml_files
    ./layout/NoteWindow.qml
    ./layout/FooterView.qml
    ./layout/NoteMenuBar.qml
    ./layout/ExportView.qml
    ./layout/LangModel.qml
    ./layout/ExportSetting.qml
    ./layout/UpdateWindow.qml
    ./layout/LanguageModel.qml
)

set(qml_resource_files
    ./images/logo.png
    ./images/arrow_left.png
    ./images/arrow_right.png
    ./images/double_arrow_left.png
    ./images/double_arrow_right.png
)
set(ts_files
    ./translations/zh_CN.ts
    ./translations/en_US.ts
    ./translations/zh_TW.ts
    ./translations/ja_JP.ts
)

qt_add_executable(SupernoteApp
    ${app_icon_resource_windows}
    ${include_files}
    ${src_files}
)

#这里添加可以在C++中使用
qt_add_resources(SupernoteApp "doc"
    PREFIX
    "/"
    FILES
    doc/new_docx.docx
    images/sn_icon.png
)

#set output path
set_source_files_properties(${ts_files}
    PROPERTIES OUTPUT_LOCATION "${CMAKE_CURRENT_BINARY_DIR}/translations")

qt_add_translations(SupernoteApp
    TS_FILES
    ${ts_files}
    QM_FILES_OUTPUT_VARIABLE qm_files
)

#install qm
install(FILES ${qm_files} DESTINATION "translations")

#增加到资源文件
qt_add_resources(SupernoteApp "translations"
    PREFIX "/"
    BASE "${CMAKE_CURRENT_BINARY_DIR}/translations"
    FILES "${qm_files}"
)

qt_add_qml_module(SupernoteApp
    URI Supernote
    VERSION 1.0
    QML_FILES ${qml_files}
    RESOURCES ${qml_resource_files}
)



#注意放置位置，靠前会报错要在qt_add_executable之后
target_include_directories(SupernoteApp PRIVATE
    ${Docx_INCLUDES}
    ${Note_INCLUDES}
    ${IINK_INCLUDES}
)

set_target_properties(SupernoteApp PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

#Currently, the recognition library is only available in the windows version
if(WIN32)
    target_link_libraries(SupernoteApp PRIVATE
         Qt6::Quick
         Qt6::Network
         iink
         Note.dll
         Docx.dll
    )
else()
    target_link_libraries(SupernoteApp PRIVATE
        Qt6::Quick
        Qt6::Network
        libNote.so
        libDocx.so
    )

endif()

install(TARGETS SupernoteApp
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
