#include <catch2/catch_all.hpp>
#include <catch2/catch_test_macros.hpp>

#include "../src/pdp/pdp.h"

TEST_CASE("Fetch") {
    SECTION("OPR") {
        PDP8I pdp8i;
        pdp8i.mem.mem[0].data[0] = 07000;
    }
}