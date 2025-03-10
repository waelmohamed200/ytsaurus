
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
add_executable(footprint)


target_link_libraries(footprint PUBLIC
  linux-headers-generic::linux-headers-generic
  contrib-libs-cxxsupp
  yutil
  library-cpp-cpuid_check
  yt-yt-ytlib
)

target_link_options(footprint PRIVATE
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

target_sources(footprint PRIVATE
  ${PROJECT_SOURCE_DIR}/yt/yt/experiments/public/footprint/main.cpp
)



target_allocator(footprint
  cpp-malloc-tcmalloc
  libs-tcmalloc-default
)

vcs_info(footprint)




