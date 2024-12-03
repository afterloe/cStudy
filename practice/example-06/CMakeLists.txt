cmake_minimum_required(VERSION 3.8)
project("MusicBox")
SET(CMAKE_CXX_STANDARD 20)

# 如果支持，请为 MSVC 编译器启用热重载。
if (POLICY CMP0141)
    cmake_policy(SET CMP0141 NEW)
    set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif ()

# 使用pkg-config 配置 第三方库
find_package(PkgConfig REQUIRED)

# 定义 ffmpeg 然后加入需要用到的库
pkg_check_modules(ffmpeg REQUIRED IMPORTED_TARGET libavdevice
        libavformat
        libavfilter
        libavcodec
        libswresample
        libswscale
        libavutil)

# 定义 sdl 库，然后加到 需要用到的库中
pkg_check_modules(sdl REQUIRED IMPORTED_TARGET sdl2)

# 头文件
include_directories(
        ${PROJECT_NAME} ./include
        ffmpeg /usr/local/ffmpeg/include
        sdl /usr/local/include/SDL2
)

# 源文件 全放到 变量中
aux_source_directory(. SRC_LIST)
# 编译生成一个对象
add_executable(${PROJECT_NAME} ${SRC_LIST})

# 连接静态库 -  13行定义的 ffmpeg
target_link_libraries(${PROJECT_NAME} PRIVATE PkgConfig::ffmpeg PkgConfig::sdl)

if (CMAKE_VERSION VERSION_GREATER 3.12)
    set_property(TARGET ${NAME} PROPERTY CXX_STANDARD 20)
endif ()
