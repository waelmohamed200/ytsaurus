
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
add_subdirectory(JITLink)
add_subdirectory(MCJIT)
add_subdirectory(Orc)
add_subdirectory(RuntimeDyld)
add_library(llvm16-lib-ExecutionEngine)


target_compile_options(llvm16-lib-ExecutionEngine PRIVATE
  $<IF:$<CXX_COMPILER_ID:MSVC>,,-Wno-everything>
)

target_include_directories(llvm16-lib-ExecutionEngine PRIVATE
  ${PROJECT_SOURCE_DIR}/contrib/libs/llvm16/lib/ExecutionEngine
)

target_link_libraries(llvm16-lib-ExecutionEngine PUBLIC
  linux-headers-generic::linux-headers-generic
  contrib-libs-cxxsupp
  contrib-libs-llvm16
  libs-llvm16-include
  ExecutionEngine-Orc-TargetProcess
  lib-ExecutionEngine-RuntimeDyld
  llvm16-lib-IR
  llvm16-lib-MC
  llvm16-lib-Object
  llvm16-lib-Support
  llvm16-lib-Target
  llvm16-lib-TargetParser
)

target_sources(llvm16-lib-ExecutionEngine PRIVATE
  ${PROJECT_SOURCE_DIR}/contrib/libs/llvm16/lib/ExecutionEngine/ExecutionEngine.cpp
  ${PROJECT_SOURCE_DIR}/contrib/libs/llvm16/lib/ExecutionEngine/ExecutionEngineBindings.cpp
  ${PROJECT_SOURCE_DIR}/contrib/libs/llvm16/lib/ExecutionEngine/GDBRegistrationListener.cpp
  ${PROJECT_SOURCE_DIR}/contrib/libs/llvm16/lib/ExecutionEngine/SectionMemoryManager.cpp
  ${PROJECT_SOURCE_DIR}/contrib/libs/llvm16/lib/ExecutionEngine/TargetSelect.cpp
)






