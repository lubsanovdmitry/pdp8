add_executable(pdp8 main.cpp)
target_link_directories(pdp8 PRIVATE .)
target_compile_features(pdp8 PRIVATE cxx_std_20)