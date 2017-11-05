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
