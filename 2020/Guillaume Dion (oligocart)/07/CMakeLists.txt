file(GLOB SRCS "*")
add_executable(AoC_2020_07 ${SRCS})

target_include_directories(AoC_2020_07 INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}")
