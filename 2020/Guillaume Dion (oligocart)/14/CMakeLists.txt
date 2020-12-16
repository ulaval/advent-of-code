file(GLOB SRCS "*")
add_executable(AoC_2020_14 ${SRCS})

target_include_directories(AoC_2020_14 INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}")
