cmake_minimum_required (VERSION 3.8)

project ("Examination")
SET(CMAKE_CXX_STANDARD 20)


include_directories(${NAME} Examination.h)

add_executable (Examination "examination.c" "main.c")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Examination PROPERTY CXX_STANDARD 20)
endif()
