set(cpa_s
    Mem.c
    File.c
)

add_library(cpa SHARED ${cpa_s})

set_target_properties(cpa PROPERTIES
    OUTPUT_NAME CPA-${CMAKE_C_COMPILER_ARCHITECTURE_ID}
)

add_executable(main Main.c)
target_link_libraries(main cpa)
