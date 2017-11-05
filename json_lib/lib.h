#ifndef JSON_LIB_MAIN_FILE
#define JSON_LIB_MAIN_FILE

#include <memory>

extern bool doVariantTest();

struct JsonValue_Impl; //Opaque pointer - PIMPL pattern

struct JsonObject
{
    JsonObject() {}
};

struct JsonArray {
    JsonArray() {}
};

class JsonValue {
private:
    JsonValue_Impl* ptr;

public:
    bool isString() const;
    bool isNumber() const;
    bool isBool()   const;
    bool isNull()   const;
    bool isObject() const;
    bool isArray()  const;
    JsonValue(const std::string& val);
    JsonValue(double val);
    JsonValue(bool val);
    JsonValue(decltype(nullptr) n);
    JsonValue(const JsonObject& val);
    JsonValue(const JsonArray& val);
    ~JsonValue();

};

#endif //JSON_LIB_MAIN_FILE
