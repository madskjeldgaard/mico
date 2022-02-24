add_library(encoder-mico INTERFACE)

target_sources(encoder-mico INTERFACE
  ${CMAKE_CURRENT_LIST_DIR}/msa301.cpp
)

# pico_generate_pio_header(encoder-mico ${CMAKE_CURRENT_LIST_DIR}/encoder.pio)

target_include_directories(encoder-mico INTERFACE ${CMAKE_CURRENT_LIST_DIR})

# Pull in pico libraries that we need
target_link_libraries(encoder-mico INTERFACE pico_stdlib hardware_i2c)
