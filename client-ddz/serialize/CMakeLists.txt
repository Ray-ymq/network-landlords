cmake_minimum_required(VERSION 3.16)
project(serialize)

# 搜索当前目录下的所有源文件
aux_source_directory(./ SRC)
file(GLOB HEAD ./*.h)
# 将当前目录下的源文件制作成静态库
add_library(serialize ${SRC} ${HEAD}
    codec.h codec.cpp)

set(PROTOBUF_LIB_DIR "C:/Protobuf/lib")
find_library(PROTOBUF_DEBUG_LIB NAMES protobufd PATHS ${PROTOBUF_LIB_DIR} NO_DEFAULT_PATH)
find_library(PROTOBUF_RELEASE_LIB NAMES protobuf PATHS ${PROTOBUF_LIB_DIR} NO_DEFAULT_PATH)

if(PROTOBUF_RELEASE_LIB AND PROTOBUF_DEBUG_LIB)
    target_link_libraries(serialize PRIVATE
        Qt${QT_VERSION_MAJOR}::Core
        debug ${PROTOBUF_DEBUG_LIB}
        optimized ${PROTOBUF_RELEASE_LIB}
    )
elseif(PROTOBUF_RELEASE_LIB)
    target_link_libraries(serialize PRIVATE Qt${QT_VERSION_MAJOR}::Core ${PROTOBUF_RELEASE_LIB})
elseif(PROTOBUF_DEBUG_LIB)
    message(WARNING "Release Protobuf library not found. Falling back to debug Protobuf for all configs.")
    target_link_libraries(serialize PRIVATE Qt${QT_VERSION_MAJOR}::Core ${PROTOBUF_DEBUG_LIB})
else()
    message(FATAL_ERROR "No Protobuf library found under ${PROTOBUF_LIB_DIR}")
endif()
