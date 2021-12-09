cmake_minimum_required(VERSION 3.0.0)
set(SERVICE_NAME dbusExample)
project(${SERVICE_NAME})

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC -Wall")
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

set(GDBUS_LIB_NAME gdbusCodegenGlibmm)
set(PROJECT_DESTINATION "/opt/test")
set(PROJECT_LIB_DESTINATION "/opt/test/lib")
set(CODEGEN_CMD gdbus-codegen-glibmm3)
set(CODEGEN_TARGET ${SERVICE_NAME}-codegen)
set(SERVICE_XML "${CMAKE_SOURCE_DIR}/gdbus/interface.xml")

#### 임의로 만든 pkg-config 파일의 경로를 /usr/x86_linux.../pkgconifg/ 경로에서 임의 경로로 설정 ####
set(ENV{PKG_CONFIG_PATH} "/opt/test/lib/pkgconfig/:$ENV{PKG_CONFIG_PATH}")

#### pkg-config 사용하여 라이브러리 검색 ####
include(FindPkgConfig)
pkg_check_modules(GIOMM REQUIRED giomm-2.4)
pkg_check_modules(GLIBMM REQUIRED glibmm-2.4)
pkg_check_modules(GLIB REQUIRED glib-2.0)
pkg_check_modules(HELLOHAL REQUIRED IHelloHal)
#### pkg-config 사용하여 라이브러리 검색 ####

set(GEN_HEADER_SRC
	${CMAKE_BINARY_DIR}/gen/testGenCode_common.h
	${CMAKE_BINARY_DIR}/gen/testGenCode_proxy.h
)

set(SERVICE_GEN_SRC
	${CMAKE_BINARY_DIR}/gen/testGenCode_common.cpp
	${CMAKE_BINARY_DIR}/gen/testGenCode_proxy.cpp
	${CMAKE_BINARY_DIR}/gen/testGenCode_stub.cpp
	${CMAKE_BINARY_DIR}/gen/testGenCode_common.h
	${CMAKE_BINARY_DIR}/gen/testGenCode_proxy.h
	${CMAKE_BINARY_DIR}/gen/testGenCode_stub.h
)

add_custom_command(
	OUTPUT ${SERVICE_GEN_SRC}
	COMMAND mkdir -p ${CMAKE_BINARY_DIR}/gen
	COMMAND sudo mkdir -p /opt/test
	COMMAND sudo mkdir -p /opt/test/include
	COMMAND sudo mkdir -p /opt/test/include/gen
	COMMAND ${CODEGEN_CMD} ${SERVICE_XML} --generate-cpp-code=${CMAKE_BINARY_DIR}/gen/testGenCode
	DEPENDS ${SERVICE_XML}
	COMMAND sudo install ${GEN_HEADER_SRC} /opt/test/include/gen
	COMMENT "Generate gdbus code"
)

#### Library 생성 ####
#### gdbusCodegenGlibmm ####
add_library(${GDBUS_LIB_NAME} STATIC ${SERVICE_GEN_SRC})

target_include_directories (
	${GDBUS_LIB_NAME} PUBLIC
	include
	${CMAKE_BINARY_DIR}/include
	${GLIBMM_INCLUDE_DIRS}
	${GIOMM_INCLUDE_DIRS}
	/opt/test/include/gen
)

target_link_libraries (
	${GDBUS_LIB_NAME} PUBLIC
	pthread
	${GLIBMM_LDFLAGS}
	${GIOMM_LDFLAGS}
)

#### pkg-config 파일 생성 ####
configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/gdbusCodegenGlibmm.pc.in
    ${CMAKE_CURRENT_SOURCE_DIR}/gdbusCodegenGlibmm.pc
    @ONLY
)

install(
    FILES ${CMAKE_CURRENT_SOURCE_DIR}/gdbusCodegenGlibmm.pc
    DESTINATION /opt/test/lib/pkgconfig
)
#### pkg-config 파일 복사 ####

install(TARGETS ${GDBUS_LIB_NAME} DESTINATION /opt/test/lib)
#### gdbusCodegenGlibmm ####
#### Library 생성 ####

#### Server Binary 생성 및 복사 ####
ADD_EXECUTABLE(${SERVICE_NAME}_Server src/main.cpp)

target_include_directories (
	${SERVICE_NAME}_Server PUBLIC
	${GLIBMM_INCLUDE_DIRS}
	${GIOMM_INCLUDE_DIRS}
	${HELLOHAL_INCLUDE_DIRS}
	include
	${CMAKE_BINARY_DIR}/gen
)

target_sources (
	${SERVICE_NAME}_Server PRIVATE
	src/main.cpp
	src/genCodeController.cpp
	src/genCodeService.cpp
)

target_link_libraries (
	${SERVICE_NAME}_Server PRIVATE
	${GLIBMM_LDFLAGS}
	${GIOMM_LDFLAGS}
	${GDBUS_LIB_NAME}
	${HELLOHAL_LDFLAGS}
	-lpthread
	${CMAKE_DL_LIBS}
)

install(TARGETS ${SERVICE_NAME}_Server DESTINATION /opt/test/bin)
#### Server Binary 생성 및 복사 ####
