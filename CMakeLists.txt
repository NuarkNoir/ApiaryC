cmake_minimum_required(VERSION 3.14)

include(cmake/prelude.cmake)

project(
    ApiaryC
    VERSION 0.1.0
    DESCRIPTION "Short description"
    HOMEPAGE_URL "https://example.com/"
    LANGUAGES C
)

include(cmake/project-is-top-level.cmake)
include(cmake/variables.cmake)

# ---- Declare library ----

add_library(
    ApiaryC_lib OBJECT
    source/lib.c
)

target_include_directories(
    ApiaryC_lib ${warning_guard}
    PUBLIC
    "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/source>"
)

target_compile_features(ApiaryC_lib PUBLIC c_std_11)

# ---- Declare executable ----

add_executable(ApiaryC_exe source/main.c)
add_executable(ApiaryC::exe ALIAS ApiaryC_exe)

set_property(TARGET ApiaryC_exe PROPERTY OUTPUT_NAME ApiaryC)

target_compile_features(ApiaryC_exe PRIVATE c_std_11)

target_link_libraries(ApiaryC_exe PRIVATE ApiaryC_lib)

# ---- Install rules ----

if(NOT CMAKE_SKIP_INSTALL_RULES)
  include(cmake/install-rules.cmake)
endif()

# ---- Developer mode ----

if(NOT ApiaryC_DEVELOPER_MODE)
  return()
elseif(NOT PROJECT_IS_TOP_LEVEL)
  message(
      AUTHOR_WARNING
      "Developer mode is intended for developers of ApiaryC"
  )
endif()

include(cmake/dev-mode.cmake)
