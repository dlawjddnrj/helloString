cmake_minimum_required(VERSION 3.0.0)
set(SERVICE_NAME dbusExample)
project(${SERVICE_NAME})

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC -Wall")
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

set(HELLO_SRC "~/hello")
set(HELLO_LIB_SRC "~/hello/lib")
set(HELLO_LIB_NAME IHelloHal)

set(ENV{PKG_CONFIG_PATH} "$ENV{HOME}/hello/lib/pkgconfig/:$ENV{PKG_CONFIG_PATH}")

#### pkg-config 사용하여 라이브러리 검색 ####
include(FindPkgConfig)
pkg_check_modules(GIOMM REQUIRED giomm-2.4)
pkg_check_modules(GLIBMM REQUIRED glibmm-2.4)
pkg_check_modules(GLIB REQUIRED glib-2.0)
#### pkg-config 사용하여 라이브러리 검색 ####

#### 필요한 header 파일 복사 ####
install(
	FILES	${CMAKE_CURRENT_SOURCE_DIR}/include/IhelloHal.h
	DESTINATION ~/hello/include/IhelloHal
)
#### 필요한 header 파일 복사 ####

#### pkg-config 파일 생성 ####
configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/IHelloHal.pc.in
    ${CMAKE_CURRENT_SOURCE_DIR}/IHelloHal.pc
    @ONLY
)

install(
    FILES ${CMAKE_CURRENT_SOURCE_DIR}/IHelloHal.pc
    DESTINATION ~/hello/lib/pkgconfig
)
#### pkg-config 파일 복사 ####