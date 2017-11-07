/*
MIT License

Copyright (c) 2017 Boris Martin

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include "catch.hpp"
#include "json_types.h"

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
    CHECK_THROWS(ref.toNumber());
    CHECK_NOTHROW(ref.toBool());
}

TEST_CASE("JsonValue is default-constructed as Null", "[JsoNValue]") {
    JsonValue val;
    CHECK(val.isNull());
}
