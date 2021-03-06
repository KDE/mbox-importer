configure_file(mboximporter-version.h.cmake ${CMAKE_CURRENT_BINARY_DIR}/mboximporter-version.h @ONLY)

set(mboximporter_SRCS
    main.cpp
    mboxmainwindow.cpp
    mboximporterinfogui.cpp
    mboximportwidget.cpp
    mboximportkernel.cpp
    )

ki18n_wrap_ui(mboximporter_SRCS
    ui/mboximportwidget.ui
    )

add_executable(mboximporter ${mboximporter_SRCS})
if (COMPILE_WITH_UNITY_CMAKE_SUPPORT)
    set_target_properties(mboximporter PROPERTIES UNITY_BUILD ON)
endif()
target_link_libraries(mboximporter
    PRIVATE
    KF5::AkonadiCore
    KF5::IdentityManagement
    KF5::MailImporterAkonadi
    KF5::MailCommon
    KF5::I18n
    KF5::Crash
    )

install(TARGETS mboximporter  ${KDE_INSTALL_TARGETS_DEFAULT_ARGS} )

install(PROGRAMS org.kde.mboximporter.desktop DESTINATION ${KDE_INSTALL_APPDIR})
