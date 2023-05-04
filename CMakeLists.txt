#####
# @Author: Darth_Eternalfaith darth_ef@hotmail.com
# @Date: 2023-04-20 00:58:11
# @LastEditors: Darth_Eternalfaith darth_ef@hotmail.com
# @LastEditTime: 2023-04-24 04:22:40
# @FilePath: \cnml\CMakeLists.txt
# @Description: CMake配置
# @
# @Copyright (c) 2023 by ${git_name} ${git_email}, All Rights Reserved. 
#####
cmake_minimum_required(VERSION 3.10)

project (NML)

# open * 初始化输出目录 * open
    # 清空输出目录，防止旧文件影响新的生成结果
        add_custom_target(clean-out COMMAND ${CMAKE_COMMAND} -E remove_directory "${CMAKE_CURRENT_SOURCE_DIR}/out")
    # 创建输出目录和子目录
        add_custom_target(create-out-dir ALL COMMAND ${CMAKE_COMMAND} -E make_directory "${CMAKE_CURRENT_SOURCE_DIR}/out")
        add_custom_target(create-lib-dir ALL COMMAND ${CMAKE_COMMAND} -E make_directory "${CMAKE_CURRENT_SOURCE_DIR}/out/lib")
        add_custom_target(create-dll-dir ALL COMMAND ${CMAKE_COMMAND} -E make_directory "${CMAKE_CURRENT_SOURCE_DIR}/out/dll")
        add_custom_target(create-test-dir ALL COMMAND ${CMAKE_COMMAND} -E make_directory "${CMAKE_CURRENT_SOURCE_DIR}/out/test")
    # 执行初始化输出目录
        add_dependencies(create-out-dir clean-out)
        add_dependencies(create-lib-dir create-out-dir)
        add_dependencies(create-dll-dir create-out-dir)
        add_dependencies(create-test-dir create-out-dir)
    # 指定输出路径
        SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY  ${PROJECT_SOURCE_DIR}/out/lib)
        SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY  ${PROJECT_SOURCE_DIR}/out/dll)
        SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY  ${PROJECT_SOURCE_DIR}/out/test)
# end  * 初始化输出目录 * end 


# open * 设置编译文件 * open
    file(GLOB SRC_FILES
        "${PROJECT_SOURCE_DIR}/src/**.c"
        "${PROJECT_SOURCE_DIR}/src/**.h"
        "${PROJECT_SOURCE_DIR}/src/**.hpp"
        "${PROJECT_SOURCE_DIR}/src/**.cpp"
    )
    message(STATUS "\n\nSRC_FILES: \n ${SRC_FILES}")
# end  * 设置编译文件 * end 


# open * 分库编译 * open
    list(REMOVE_ITEM SRC_FILES "${PROJECT_SOURCE_DIR}/src/test.cpp")
    # 静态库
        add_library(${CMAKE_PROJECT_NAME}_lib STATIC ${SRC_FILES})
        set_target_properties(${CMAKE_PROJECT_NAME}_lib PROPERTIES PREFIX "" OUTPUT_NAME "${CMAKE_PROJECT_NAME}")

    # 动态库
        add_library(${CMAKE_PROJECT_NAME}_dll SHARED ${SRC_FILES})
        set_target_properties(${CMAKE_PROJECT_NAME}_dll PROPERTIES PREFIX "" OUTPUT_NAME "${CMAKE_PROJECT_NAME}")

    # 测试例
        add_executable(${CMAKE_PROJECT_NAME}_test ${PROJECT_SOURCE_DIR}/src/test.cpp)
        target_link_libraries(${CMAKE_PROJECT_NAME}_test ${CMAKE_PROJECT_NAME}_dll)
# end  * 分库编译 * end 

# open * 直接编译 * open
    # add_executable(${CMAKE_PROJECT_NAME}_test ${SRC_FILES})
# end  * 直接编译 * end 
