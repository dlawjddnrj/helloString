cmake_minimum_required(VERSION 3.0.0)
set(SERVICE_NAME dbusExample)
project(${SERVICE_NAME})

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC -Wall")
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

set(PROJECT_DESTINATION "/opt/test")
set(PROJECT_LIB_DESTINATION "/opt/test/lib")
set(ENV{PKG_CONFIG_PATH} "/opt/test/lib/pkgconfig/:$ENV{PKG_CONFIG_PATH}")

#### pkg-config 사용하여 라이브러리 검색 ####
find_package(PkgConfig)
pkg_check_modules(GIOMM REQUIRED giomm-2.4)
pkg_check_modules(GLIBMM REQUIRED glibmm-2.4)
pkg_check_modules(GLIB REQUIRED glib-2.0)
pkg_check_modules(CLIENTCOMMON REQUIRED clientCommon)
#### pkg-config 사용하여 라이브러리 검색 ####

#### Client B ####
ADD_EXECUTABLE(${SERVICE_NAME}_Client_B src/mainClient2.cpp)

target_include_directories(
	${SERVICE_NAME}_Client_B PUBLIC
	${GLIBMM_INCLUDE_DIRS}
	${GIOMM_INCLUDE_DIRS}
	${CLIENTCOMMON_INCLUDE_DIRS}
)

target_sources (
	${SERVICE_NAME}_Client_B PRIVATE
	src/mainClient2.cpp
)

find_library(CHECK_LIBRARY
	NAMES clientCommon
	PATHS ${PROJECT_LIB_DESTINATION}
)

target_link_libraries(
	${SERVICE_NAME}_Client_B PUBLIC
	${GLIBMM_LDFLAGS}
	${GIOMM_LDFLAGS}
	${CHECK_LIBRARY}
	-lpthread
)

install(TARGETS ${SERVICE_NAME}_Client_B DESTINATION ${PROJECT_DESTINATION}/bin/B)
#### Client B ####
