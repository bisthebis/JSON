#include "lib.h"
#include <boost/variant.hpp>

extern bool doVariantTest() {
    using boost::variant;
    using boost::get;
    using std::string;

    variant<string, double, bool> var;
    var = false;
    if (get<bool>(var))
        return false;
    {
        var = string("Hello world");
        string& str = get<string>(var);
        str += " !";
    }
    if (get<string>(var) != "Hello world !")
        return false;
    var = double(9.0 / 3);
    if (get<double>(var) * 3 != 9)
        return false;

    return true;
}


class JsonValue_Impl {
    //Either a primitive (string, double, bool, null = nullptr), an object or an array
private:
    using null = decltype(nullptr);
    boost::variant<std::string, double, bool, null, JsonObject, JsonArray> value;

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
    return  type == 0;
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
    return  type == 3;
}

bool JsonValue::isObject() const {
    auto type = ptr->type();
    return  type == 4;
}

bool JsonValue::isArray() const {
    auto type = ptr->type();
    return  type == 5;
}

JsonValue::JsonValue(const std::string &val)    :   ptr(new JsonValue_Impl(val)) {}
JsonValue::JsonValue(double val)                :   ptr(new JsonValue_Impl(val)) {}
JsonValue::JsonValue(bool val)                  :   ptr(new JsonValue_Impl(val)) {}
JsonValue::JsonValue(decltype(nullptr) n)       :   ptr(new JsonValue_Impl(nullptr)) {}
JsonValue::JsonValue(const JsonArray &val)      :   ptr(new JsonValue_Impl(val)) {}
JsonValue::JsonValue(const JsonObject &val)     :   ptr(new JsonValue_Impl(val)) {}
JsonValue::~JsonValue()  {delete ptr;}
