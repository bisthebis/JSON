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
#ifndef JSONVALUE_H
#define JSONVALUE_H

#include <memory>
#include <map>
#include <vector>

struct JsonValue_Impl; //Opaque pointer - PIMPL pattern
struct JsonValue;

class JsonObject
{
private:
    std::map<std::string, JsonValue> data;

public:
    JsonObject() = default;
    JsonValue& operator [](const std::string& index) noexcept; //If not found, create a default null value (normal behavior of std::map)
    auto find(const std::string& index) const noexcept -> decltype(data.cbegin());
    auto find(const std::string& index) noexcept -> decltype(data.begin());

};

struct JsonArray {
    JsonArray() = default;
};

class JsonValue {
private:
    JsonValue_Impl* ptr;

public:
    //Type checkers
    bool isString() const;
    bool isNumber() const;
    bool isBool()   const;
    bool isNull()   const;
    bool isObject() const;
    bool isArray()  const;

    //Accessors & their const counterpart. Throws std::runtime error if type is wrong !
    std::string& toString();
    const std::string& toString() const;

    double& toNumber();
    double toNumber() const;

    bool& toBool();
    bool toBool() const;
    explicit operator bool() const {return toBool();}

    std::nullptr_t toNull() const;

    JsonArray& toArray();
    const JsonArray& toArray() const;

    JsonObject& toObject();
    const JsonObject& toObject() const;

    //Constructors
    JsonValue();
    JsonValue(const std::string& val);
    JsonValue(double val);
    JsonValue(bool val);
    JsonValue(decltype(nullptr) n);
    JsonValue(const JsonObject& val);
    JsonValue(const JsonArray& val);
    ~JsonValue();

};

#endif // JSONVALUE_H
