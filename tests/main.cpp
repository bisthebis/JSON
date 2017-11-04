#define CATCH_CONFIG_MAIN
#include "catch.hpp"

TEST_CASE("Dummy", "[dummy]") {
    REQUIRE (5*5 == 25);
}
