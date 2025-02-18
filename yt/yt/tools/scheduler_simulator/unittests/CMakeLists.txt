
# This file was generated by the build system used internally in Yandex and called "ya"
# (https://github.com/yandex/yatool).
#
# Configuration files of ya build system are usually named ya.make. If ya.make file is present
# at the root of the repository, then this repository supports ya build. 
# 
# If the repository supports both CMake and ya build configurations, please modify both of them.
#
# If only CMake build configuration is supported then modify only CMake files and note that only
# simple modifications are allowed like adding source-files to targets or adding simple properties
# like target_include_directories. These modifications will be ported to original ya.make files
# by maintainers. Any complex modifications which can't be easily ported back to the ya build 
# system may be rejected.

find_package(linux-headers-generic REQUIRED)
add_executable(unittester-scheduler-simulator)


target_compile_options(unittester-scheduler-simulator PRIVATE
  -Wdeprecated-this-capture
)

target_include_directories(unittester-scheduler-simulator PRIVATE
  ${PROJECT_SOURCE_DIR}/yt/yt/tools/scheduler_simulator
)

target_link_libraries(unittester-scheduler-simulator PUBLIC
  linux-headers-generic::linux-headers-generic
  contrib-libs-cxxsupp
  yutil
  library-cpp-cpuid_check
  cpp-testing-gtest
  cpp-testing-gtest_main
  yt-tools-scheduler_simulator
  yt-core-test_framework
)

target_link_options(unittester-scheduler-simulator PRIVATE
  -ldl
  -lrt
  -Wl,--no-as-needed
  -fPIC
  -fPIC
  -lpthread
  -lrt
  -ldl
  -lutil
)

target_sources(unittester-scheduler-simulator PRIVATE
  ${PROJECT_SOURCE_DIR}/yt/yt/tools/scheduler_simulator/unittests/operation_controller_ut.cpp
  ${PROJECT_SOURCE_DIR}/yt/yt/tools/scheduler_simulator/unittests/control_thread_ut.cpp
)


add_test(
  NAME
  unittester-scheduler-simulator
  COMMAND
  unittester-scheduler-simulator
)

set_property(
  TEST
  unittester-scheduler-simulator
  PROPERTY
  LABELS
  SMALL
)

set_property(
  TEST
  unittester-scheduler-simulator
  PROPERTY
  PROCESSORS
  1
)

set_property(
  TEST
  unittester-scheduler-simulator
  PROPERTY
  ENVIRONMENT
)


target_allocator(unittester-scheduler-simulator
  cpp-ytalloc-impl
)

vcs_info(unittester-scheduler-simulator)




