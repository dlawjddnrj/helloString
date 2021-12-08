cmake_minimum_required(VERSION 3.0.0)
set(SERVICE_NAME dbusExample)
project(${SERVICE_NAME})

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC -Wall")
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

set(HELLO_SRC "~/hello")
set(COMMON_LIB_NAME clientCommon)
set(HELLO_LIB_SRC "~/hello/lib")

set(SRC_PROXY
	${CMAKE_CURRENT_SOURCE_DIR}/src/genCodeProxy.cpp
)
#### 임의로 만든 pkg-config 파일의 경로를 /usr/x86_linux.../pkgconifg/ 경로에서 임의 경로로 설정 ####
set(ENV{PKG_CONFIG_PATH} "$ENV{HOME}/hello/lib/pkgconfig/:$ENV{PKG_CONFIG_PATH}")

#### pkg-config 사용하여 라이브러리 검색 ####
find_package(PkgConfig)
pkg_check_modules(GIOMM REQUIRED giomm-2.4)
pkg_check_modules(GLIBMM REQUIRED glibmm-2.4)
pkg_check_modules(GLIB REQUIRED glib-2.0)
pkg_check_modules(GDBUSCODEGENGLIBMM REQUIRED gdbusCodegenGlibmm)
#### pkg-config 사용하여 라이브러리 검색 ####

#### Library 생성 ####
#### clientCommon ####
add_library (${COMMON_LIB_NAME} SHARED ${SRC_PROXY})

target_include_directories (
	${COMMON_LIB_NAME} PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/include
	${GLIBMM_INCLUDE_DIRS}
	${GIOMM_INCLUDE_DIRS}
	${GDBUSCODEGENGLIBMM_INCLUDE_DIRS}
)

find_library(CHECK_LIBRARY
	NAMES gdbusCodegenGlibmm
	PATHS ~/hello/lib
)

target_link_libraries (
	${COMMON_LIB_NAME} PUBLIC
	${GLIBMM_LDFLAGS}
	${GIOMM_LDFLAGS}
	${CHECK_LIBRARY}
	-lpthread
)

#### pkg-config 파일 생성 ####
configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/clientCommon.pc.in
    ${CMAKE_CURRENT_SOURCE_DIR}/clientCommon.pc
    @ONLY
)

install(
    FILES ${CMAKE_CURRENT_SOURCE_DIR}/clientCommon.pc
    DESTINATION ~/hello/lib/pkgconfig
)

#### pkg-config 파일 복사 ####

#### 라이브러리 및 필요한 header 파일 복사 ####
install(
	TARGETS ${COMMON_LIB_NAME}
	LIBRARY DESTINATION ~/hello/lib
)

install(
	FILES	${CMAKE_CURRENT_SOURCE_DIR}/include/genCodeProxy.h
		${CMAKE_CURRENT_SOURCE_DIR}/include/threadExClass.h
	DESTINATION ~/hello/include
)
#### 라이브러리 및 필요한 header 파일 복사 ####
#### clientCommon ####
#### Library 생성 ####
