#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "lib.h"


TEST_CASE("Dummy", "[dummy]") {
    REQUIRE (square(7) == 49);
}
