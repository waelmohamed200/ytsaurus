
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
add_library(orm-library-query)


target_compile_options(orm-library-query PRIVATE
  -Wdeprecated-this-capture
)

target_link_libraries(orm-library-query PUBLIC
  linux-headers-generic::linux-headers-generic
  contrib-libs-cxxsupp
  yutil
  orm-library-attributes
  library-query-engine
  yt-yt-core
  yt-yt-client
)

target_sources(orm-library-query PRIVATE
  ${PROJECT_SOURCE_DIR}/yt/yt/orm/library/query/expression_evaluator.cpp
  ${PROJECT_SOURCE_DIR}/yt/yt/orm/library/query/filter_introspection.cpp
  ${PROJECT_SOURCE_DIR}/yt/yt/orm/library/query/filter_matcher.cpp
  ${PROJECT_SOURCE_DIR}/yt/yt/orm/library/query/query_evaluator.cpp
  ${PROJECT_SOURCE_DIR}/yt/yt/orm/library/query/query_optimizer.cpp
  ${PROJECT_SOURCE_DIR}/yt/yt/orm/library/query/query_rewriter.cpp
)






