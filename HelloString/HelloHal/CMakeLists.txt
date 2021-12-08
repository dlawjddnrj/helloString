cmake_minimum_required(VERSION 3.0.0)
set(SERVICE_NAME dbusExample)
project(${SERVICE_NAME})

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC -Wall")
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

set(CMAKE_PREFIX_PATH "$ENV{HOME}/hello/lib/pkgconfig")
set(ENV{PKG_CONFIG_PATH} "$ENV{HOME}/hello/lib/pkgconfig/:$ENV{PKG_CONFIG_PATH}")
set(HELLO_SRC "~/hello")
set(HELLO_LIB_SRC "~/hello/lib")

find_package(PkgConfig REQUIRED)
pkg_check_modules(IHELLOHAL REQUIRED IHelloHal)
pkg_check_modules(GLIBMM REQUIRED glibmm-2.4)

set(HAL_LIB_NAME helloHal)

set(HAL_SRC
    ${CMAKE_CURRENT_SOURCE_DIR}/src/helloHal.cpp
)

add_library (${HAL_LIB_NAME} SHARED ${HAL_SRC})

target_include_directories (
	${HAL_LIB_NAME} PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/include
	${IHELLOHAL_INCLUDE_DIRS}
    ${GLIBMM_INCLUDE_DIRS}
)

target_link_libraries (
	${HAL_LIB_NAME} PUBLIC
	${IHELLOHAL_LDFLAGS}
    ${GLIBMM_LDFLAGS}
    -lpthread
)

install(
    FILES ${CMAKE_CURRENT_SOURCE_DIR}/include/helloHal.h
    DESTINATION ~/hello/include/IhelloHal
)

configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/helloHal.pc.in
    ${CMAKE_CURRENT_SOURCE_DIR}/helloHal.pc
    @ONLY
)

install(
    FILES ${CMAKE_CURRENT_SOURCE_DIR}/helloHal.pc
    DESTINATION ~/hello/lib/pkgconfig
)

install(
	TARGETS ${HAL_LIB_NAME}
	LIBRARY DESTINATION ~/hello/lib
)