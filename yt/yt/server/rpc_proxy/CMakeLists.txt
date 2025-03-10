
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
add_subdirectory(unittests)
add_library(yt-server-rpc_proxy)


target_compile_options(yt-server-rpc_proxy PRIVATE
  -Wdeprecated-this-capture
)

target_link_libraries(yt-server-rpc_proxy PUBLIC
  linux-headers-generic::linux-headers-generic
  contrib-libs-cxxsupp
  yutil
  ytserver
  server-lib-chunk_pools
  server-lib-rpc_proxy
  server-lib-cypress_registrar
  yt-yt-ytlib
  yt-client-arrow
  core-rpc-grpc
  yt-library-auth_server
  yt-library-dynamic_config
  cpp-yt-phdr_cache
  library-cpp-getopt
)

target_sources(yt-server-rpc_proxy PRIVATE
  ${PROJECT_SOURCE_DIR}/yt/yt/server/rpc_proxy/access_checker.cpp
  ${PROJECT_SOURCE_DIR}/yt/yt/server/rpc_proxy/bootstrap.cpp
  ${PROJECT_SOURCE_DIR}/yt/yt/server/rpc_proxy/config.cpp
  ${PROJECT_SOURCE_DIR}/yt/yt/server/rpc_proxy/discovery_service.cpp
  ${PROJECT_SOURCE_DIR}/yt/yt/server/rpc_proxy/dynamic_config_manager.cpp
  ${PROJECT_SOURCE_DIR}/yt/yt/server/rpc_proxy/bundle_dynamic_config_manager.cpp
)






