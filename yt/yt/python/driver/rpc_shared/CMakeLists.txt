
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

find_package(Python3 REQUIRED COMPONENTS Development)
find_package(linux-headers-generic REQUIRED)
add_shared_library(driver_rpc_lib)


target_compile_options(driver_rpc_lib PRIVATE
  -DPYCXX_PYTHON_2TO3
  -DPYCXX_6_2_COMPATIBILITY
  -DPy_LIMITED_API=0x03040000
  -Wno-register
)

target_link_libraries(driver_rpc_lib PUBLIC
  linux-headers-generic::linux-headers-generic
  contrib-libs-cxxsupp
  yutil
  Python3::Module
  python-driver-rpc
)

target_link_options(driver_rpc_lib PRIVATE
  -ldl
  -lrt
  -Wl,--no-as-needed
  -fPIC
  -Wl,-z,notext
  -Wl,-Bsymbolic
  -fPIC
  -lpthread
  -lrt
  -ldl
  -lutil
)



use_export_script(driver_rpc_lib
  ${PROJECT_SOURCE_DIR}/yt/yt/python/driver/rpc_shared/driver_rpc3.exports
)

vcs_info(driver_rpc_lib)




