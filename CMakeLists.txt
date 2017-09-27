cmake_minimum_required(VERSION 3.3)

include("cmake/HunterGate.cmake")
HunterGate(
    URL "https://github.com/rusdevops/hunter/archive/v0.19.109.6.tar.gz"
    SHA1 "1d5ec3d14107ef4fd5ac40af1ab9aa82680fdbe3"
)

set(MARC_VERSION_MAJOR 0)
set(MARC_VERSION_MINOR 4)
set(MARC_VERSION_PATCH 0)
set(MARC_VERSION ${MARC_VERSION_MAJOR}.${MARC_VERSION_MINOR}.${MARC_VERSION_PATCH})

project(MARC VERSION ${MARC_VERSION})

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(BUILD_TESTS "Build tests" OFF)

hunter_add_package(CURLCPP)
find_package(CURLCPP CONFIG REQUIRED)

hunter_add_package(jsoncpp)
find_package(jsoncpp CONFIG REQUIRED)


file(GLOB ${PROJECT_NAME}_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/sources/*.cpp")
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include/)

add_library(libmarc ${${PROJECT_NAME}_SOURCES})
set_target_properties(libmarc PROPERTIES PREFIX "")
set_target_properties(libmarc PROPERTIES IMPORT_PREFIX "")


target_link_libraries(libmarc jsoncpp_lib_static CURLCPP::libcurlcpp)

target_include_directories(libmarc PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

# Install

set(GENERATED_DIR "${CMAKE_CURRENT_BINARY_DIR}/generated")

set(CONFIG_INSTALL_DIR "lib/cmake/${PROJECT_NAME}")
set(INCLUDE_INSTALL_DIR "include")

set(VERSION_CONFIG "${GENERATED_DIR}/${PROJECT_NAME}ConfigVersion.cmake")
set(PROJECT_CONFIG "${GENERATED_DIR}/${PROJECT_NAME}Config.cmake")
set(TARGETS_EXPORT_NAME "${PROJECT_NAME}Targets")
set(NAMESPACE "${PROJECT_NAME}::")

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    "${VERSION_CONFIG}" COMPATIBILITY SameMajorVersion
)

configure_package_config_file(
    "${PROJECT_SOURCE_DIR}/cmake/Config.cmake.in"
    "${PROJECT_CONFIG}"
     INSTALL_DESTINATION "${CONFIG_INSTALL_DIR}"
)

install(TARGETS libmarc
    EXPORT "${TARGETS_EXPORT_NAME}"
    RUNTIME DESTINATION bin
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
)

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/ DESTINATION include)

install(
  FILES "${PROJECT_CONFIG}" "${VERSION_CONFIG}"
  DESTINATION "${CONFIG_INSTALL_DIR}"
  )

install(EXPORT "${TARGETS_EXPORT_NAME}" 
    NAMESPACE "${NAMESPACE}" 
    DESTINATION "${CONFIG_INSTALL_DIR}"
)

if(BUILD_TESTS)
	hunter_add_package(GTest)
	find_package(GTest CONFIG REQUIRED)
	enable_testing()
	file(GLOB ${PROJECT_NAME}_TEST_SOURCES tests/*.cpp)
	add_executable(check ${${PROJECT_NAME}_TEST_SOURCES})
	target_link_libraries(check libmarc GTest::main) 
	add_test(NAME check COMMAND check) 
endif()



