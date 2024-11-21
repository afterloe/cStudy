cmake_minimum_required (VERSION 3.8)
project ("MusicBox")
SET(CMAKE_CXX_STANDARD 20)

# 如果支持，请为 MSVC 编译器启用热重载。
if (POLICY CMP0141)
    cmake_policy(SET CMP0141 NEW)
    set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

include_directories(${NAME} ./include)

add_executable (MusicBox app.cc
        Music.cc
        BiTree.cc)

if (CMAKE_VERSION VERSION_GREATER 3.12)
    set_property(TARGET ${NAME} PROPERTY CXX_STANDARD 20)
endif()
