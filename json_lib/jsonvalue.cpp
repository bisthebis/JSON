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
#include "jsonvalue.h"
#include <boost/variant.hpp>
#include <stdexcept>

class JsonValue_Impl {
    //Either a primitive (string, double, bool, null = nullptr), an object or an array
private:
    friend class JsonValue;
    using null = decltype(nullptr);
    boost::variant<null, double, bool, std::string, JsonObject, JsonArray> value;

public:
    JsonValue_Impl(const std::string& val) {value = val;}
    JsonValue_Impl(double val) {value = val;}
    JsonValue_Impl(bool val) {value = val;}
    JsonValue_Impl(null n) {value = nullptr;}
    JsonValue_Impl(const JsonObject& val) {value = val;}
    JsonValue_Impl(const JsonArray& val) {value = val;}

    int type() const {return value.which();}


    JsonValue_Impl& operator =(const auto& val){
        value = val;
        return *this;
    }
};

bool JsonValue::isString() const {
    auto type = ptr->type();
    return  type == 3;
}

bool JsonValue::isNumber() const {
    auto type = ptr->type();
    return  type == 1;
}

bool JsonValue::isBool() const {
    auto type = ptr->type();
    return  type == 2;
}

bool JsonValue::isNull() const {
    auto type = ptr->type();
    return  type == 0;
}

bool JsonValue::isObject() const {
    auto type = ptr->type();
    return  type == 4;
}

bool JsonValue::isArray() const {
    auto type = ptr->type();
    return  type == 5;
}

JsonValue::JsonValue()                          :   ptr(new JsonValue_Impl(nullptr)) {}
JsonValue::JsonValue(const std::string &val)    :   ptr(new JsonValue_Impl(val)) {}
JsonValue::JsonValue(double val)                :   ptr(new JsonValue_Impl(val)) {}
JsonValue::JsonValue(bool val)                  :   ptr(new JsonValue_Impl(val)) {}
JsonValue::JsonValue(decltype(nullptr) n)       :   ptr(new JsonValue_Impl(nullptr)) {}
JsonValue::JsonValue(const JsonArray &val)      :   ptr(new JsonValue_Impl(val)) {}
JsonValue::JsonValue(const JsonObject &val)     :   ptr(new JsonValue_Impl(val)) {}
JsonValue::~JsonValue()  {delete ptr;}


std::string& JsonValue::toString() {
    if (!isString())
        throw std::runtime_error("Called JsonValue::toString() on a non-string value");
    return boost::get<std::string>(ptr->value);
}

const std::string& JsonValue::toString() const {
    if (!isString())
        throw std::runtime_error("Called JsonValue::toString() on a non-string value");
    return boost::get<std::string>(ptr->value);
}

decltype(nullptr) JsonValue::toNull() const {
    if (!isNull())
        throw std::runtime_error("Called JsonValue::toNull() on a non-null value");
    return nullptr;
}

double& JsonValue::toNumber() {
    if (!isNumber())
        throw std::runtime_error("Called JsonValue::toNumber() on a non-number value");
    return boost::get<double>(ptr->value);
}

double JsonValue::toNumber() const {
    if (!isNumber())
        throw std::runtime_error("Called JsonValue::toNumber() on a non-number value");
    return boost::get<double>(ptr->value);
}

bool& JsonValue::toBool() {
    if (!isBool())
        throw std::runtime_error("Called JsonValue::toBool() on a non-boolean value");
    return boost::get<bool>(ptr->value);
}

bool JsonValue::toBool() const {
    if (!isBool())
        throw std::runtime_error("Called JsonValue::toBool() on a non-boolean value");
    return boost::get<bool>(ptr->value);
}

JsonArray& JsonValue::toArray() {
    if (!isArray())
        throw std::runtime_error("Called JsonValue::toArray() on a non-array value");
    return boost::get<JsonArray>(ptr->value);
}

const JsonArray& JsonValue::toArray() const {
    if (!isArray())
        throw std::runtime_error("Called JsonValue::toArray() on a non-array value");
    return boost::get<JsonArray>(ptr->value);
}

JsonObject& JsonValue::toObject() {
    if (!isArray())
        throw std::runtime_error("Called JsonValue::toObject() on a non-object value");
    return boost::get<JsonObject>(ptr->value);
}

const JsonObject& JsonValue::toObject() const {
    if (!isArray())
        throw std::runtime_error("Called JsonValue::toObject() on a non-object value");
    return boost::get<JsonObject>(ptr->value);
}

JsonValue& JsonObject::operator [](const std::string& index) noexcept {
    return data[index];
}

auto JsonObject::find(const std::string &index) const noexcept -> decltype(data.cbegin()) {
    return data.find(index);
}

auto JsonObject::find(const std::string &index) noexcept -> decltype(data.begin()) {
    return data.find(index);
}
