add_executable(test_cycles cycles.cpp ../src/pdp/pdp.cpp)
target_link_libraries(test_cycles PRIVATE Catch2::Catch2)
target_include_directories(test_cycles PRIVATE CATCH_INCLUDE_DIRS)