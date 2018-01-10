#-------------------------------------------------
#
# Project created by QtCreator 2017-09-06T11:24:52
#
#-------------------------------------------------

QT       += core gui serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TraceSystem
TEMPLATE = app

CONFIG += c++11 #Позволяет использовать константы

INCLUDEPATH += .//widgets//

RESOURCES += \
    resource.qrc

FORMS += \
    widgets/files_viewer_win.ui \
    widgets/list_point_win.ui \
    widgets/main_win.ui \
    widgets/terminal_win.ui \
    widgets/tree_files_win.ui \
    widgets/widget_system_buttons.ui \
    widgets/prefences_win.ui \
    widgets/info_about_app_win.ui \
    widgets/trace_point_proc_dialog.ui

HEADERS += \
    widgets/base_win.h \
    widgets/files_viewer_win.h \
    widgets/list_point_win.h \
    widgets/main_win.h \
    widgets/terminal_win.h \
    widgets/tree_files_win.h \
    widgets/widget_system_buttons.h \
    types/class_file_meta_item.h \
    types/trace_point_info.h \
    types/trace_point_item.h \
    entity/clang_trace_highlighter.h \
    entity/virtual_serial_port.h \
    entity/app_settings.h \
    widgets/prefences_win.h \
    widgets/info_about_app_win.h \
    entity/file_trace_points.h \
    entity/trace_point_machine.h \
    types/type_trace_point_info.h \
    widgets/trace_point_proc_dialog.h

SOURCES += \
    widgets/base_win.cpp \
    widgets/files_viewer_win.cpp \
    widgets/list_point_win.cpp \
    widgets/main_win.cpp \
    widgets/terminal_win.cpp \
    widgets/tree_files_win.cpp \
    widgets/widget_system_buttons.cpp \
    types/class_file_meta_item.cpp \
    types/trace_point_info.cpp \
    types/trace_point_item.cpp \
    entity/clang_trace_highlighter.cpp \
    main.cpp \
    entity/virtual_serial_port.cpp \
    entity/app_settings.cpp \
    widgets/prefences_win.cpp \
    widgets/info_about_app_win.cpp \
    entity/file_trace_points.cpp \
    entity/trace_point_machine.cpp \
    widgets/trace_point_proc_dialog.cpp

RC_ICONS = red_bug.ico
