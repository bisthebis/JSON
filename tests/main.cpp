#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "lib.h"


TEST_CASE("Dummy", "[dummy]") {
    CHECK (doVariantTest());
}


