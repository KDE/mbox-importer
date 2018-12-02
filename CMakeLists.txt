set(KDEPIM_VERSION_NUMBER "5.10.40")
cmake_minimum_required(VERSION 3.5)
project(mbox-importer VERSION ${KDEPIM_VERSION_NUMBER})

set(KF5_VERSION "5.51.0")

find_package(ECM ${KF5_VERSION} CONFIG REQUIRED)
set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH})
include(ECMInstallIcons)


include(ECMSetupVersion)
include(ECMAddTests)

include(GenerateExportHeader)
include(ECMGenerateHeaders)

include(FeatureSummary)
include(CheckFunctionExists)
include(ECMGeneratePriFile)

include(KDEInstallDirs)
include(KDECMakeSettings)
include(KDEFrameworkCompilerSettings NO_POLICY_SCOPE)
include(ECMAddAppIcon)
include(ECMQtDeclareLoggingCategory)


# Do NOT add quote
set(KDEPIM_DEV_VERSION alpha)

# add an extra space
if(DEFINED KDEPIM_DEV_VERSION)
    set(KDEPIM_DEV_VERSION " ${KDEPIM_DEV_VERSION}")
endif()

set(KDEPIM_VERSION "${KDEPIM_VERSION_NUMBER}${KDEPIM_DEV_VERSION}")

set(AKONADI_VERSION "5.9.80")

set(KDEPIM_LIB_VERSION "${KDEPIM_VERSION_NUMBER}")
set(KDEPIM_LIB_SOVERSION "5")

set(QT_REQUIRED_VERSION "5.9.0")
find_package(Qt5 ${QT_REQUIRED_VERSION} CONFIG REQUIRED Gui Widgets)
set(LIBMAILIMPORTER_VERSION_LIB "5.9.80")
set(MAILCOMMON_LIB_VERSION_LIB "5.9.80")
set(PIMCOMMON_LIB_VERSION "5.9.80")

# Find KF5 package
find_package(KF5Config ${KF5_VERSION} CONFIG REQUIRED)
find_package(KF5Service ${KF5_VERSION} CONFIG REQUIRED)
find_package(KF5Crash ${KF5_VERSION} REQUIRED)
find_package(KF5KIO ${KF5_VERSION} REQUIRED)

# Find KdepimLibs Package
find_package(KF5Akonadi ${AKONADI_VERSION} CONFIG REQUIRED)

find_package(KF5MailCommon ${MAILCOMMON_LIB_VERSION_LIB} CONFIG REQUIRED)
find_package(KF5MailImporterAkonadi ${LIBMAILIMPORTER_VERSION_LIB} CONFIG REQUIRED)
find_package(KF5PimCommonAkonadi ${PIMCOMMON_LIB_VERSION_LIB} CONFIG REQUIRED)
include_directories(${mbox-importer_SOURCE_DIR} ${mbox-importer_BINARY_DIR})

add_definitions(-DQT_DISABLE_DEPRECATED_BEFORE=0x060000)

add_subdirectory(src)

feature_summary(WHAT ALL FATAL_ON_MISSING_REQUIRED_PACKAGES)
