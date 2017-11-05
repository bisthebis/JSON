#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "lib.h"


TEST_CASE("Dummy", "[dummy]") {
    CHECK (doVariantTest());
}

TEST_CASE("JsonValue evaluates types corectly", "[JsonValue]") {

    JsonValue val (std::string("Hello world !"));
    CHECK(val.isString());
    CHECK_FALSE(val.isNumber());
    CHECK_FALSE(val.isBool());
    CHECK_FALSE(val.isNull());
    CHECK_FALSE(val.isObject());
    CHECK_FALSE(val.isArray());

    val = nullptr;
    CHECK_FALSE(val.isString());
    CHECK_FALSE(val.isNumber());
    CHECK_FALSE(val.isBool());
    CHECK(val.isNull());
    CHECK_FALSE(val.isObject());
    CHECK_FALSE(val.isArray());

    val = 5.0;
    CHECK_FALSE(val.isString());
    CHECK(val.isNumber());
    CHECK_FALSE(val.isBool());
    CHECK_FALSE(val.isNull());
    CHECK_FALSE(val.isObject());
    CHECK_FALSE(val.isArray());

    val = false;
    CHECK_FALSE(val.isString());
    CHECK_FALSE(val.isNumber());
    CHECK(val.isBool());
    CHECK_FALSE(val.isNull());
    CHECK_FALSE(val.isObject());
    CHECK_FALSE(val.isArray());
}

TEST_CASE("JsonValue throws if and only if bad conversion happen. (Non-const version)", "[JsonValue]") {
    JsonValue val = false;
    CHECK_THROWS(val.toString());
    CHECK_THROWS(val.toNull());
    //CHECK_THROWS()
}

TEST_CASE("JsonValue throws if and only if bad conversion happen. (Const version)", "[JsonValue]") {
    //No need to check for toNull : already covered in the non const version

    JsonValue val = false;
    const JsonValue& ref = val;
    CHECK_THROWS(ref.toString());
    //CHECK_THROWS()
}

TEST_CASE("JsonValue is default-constructed as Null", "[JsoNValue]") {
    JsonValue val;
    CHECK(val.isNull());
}
