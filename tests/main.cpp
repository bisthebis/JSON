#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "lib.h"


TEST_CASE("Dummy", "[dummy]") {
    REQUIRE (doVariantTest());
}

TEST_CASE("JsonValue evaluates types corectly", "[JsonValue]") {

    JsonValue val (std::string("Hello world !"));
    REQUIRE(val.isString());
    REQUIRE_FALSE(val.isNumber());
    REQUIRE_FALSE(val.isBool());
    REQUIRE_FALSE(val.isNull());
    REQUIRE_FALSE(val.isObject());
    REQUIRE_FALSE(val.isArray());

    val = nullptr;
    REQUIRE_FALSE(val.isString());
    REQUIRE_FALSE(val.isNumber());
    REQUIRE_FALSE(val.isBool());
    REQUIRE(val.isNull());
    REQUIRE_FALSE(val.isObject());
    REQUIRE_FALSE(val.isArray());

    val = 5.0;
    REQUIRE_FALSE(val.isString());
    REQUIRE(val.isNumber());
    REQUIRE_FALSE(val.isBool());
    REQUIRE_FALSE(val.isNull());
    REQUIRE_FALSE(val.isObject());
    REQUIRE_FALSE(val.isArray());

    val = false;
    REQUIRE_FALSE(val.isString());
    REQUIRE_FALSE(val.isNumber());
    REQUIRE(val.isBool());
    REQUIRE_FALSE(val.isNull());
    REQUIRE_FALSE(val.isObject());
    REQUIRE_FALSE(val.isArray());
}

TEST_CASE("JsonValue throws if and only if bad conversion happen. (Non-const version)", "[JsonValue]") {
    JsonValue val = false;
    REQUIRE_THROWS(val.toString());
    REQUIRE_THROWS(val.toNull());
    //REQUIRE_THROWS()
}

TEST_CASE("JsonValue throws if and only if bad conversion happen. (Const version)", "[JsonValue]") {
    //No need to check for toNull : already covered in the non const version

    JsonValue val = false;
    const JsonValue& ref = val;
    REQUIRE_THROWS(ref.toString());
    //REQUIRE_THROWS()
}
