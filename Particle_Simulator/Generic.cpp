#include "Generic.hpp"

std::string stringToLower(std::string str) {

    for (int i = 0; i < str.length(); i++) {
        str[i] = tolower(str[i]);
    }

    return str;
}

bool isIntNumber(std::string str) {

    if (str[0] == '+' || str[0] == '-') {
        str.erase(str.begin());
    }

    for (int i = 0; i < str.length(); i++) {
        if (str[i] - '0' < 0 || str[i] - '0' > 9) {
            return false;
        }

    }

    return true;
}

bool isDecimalNumber(std::string str) {

    if (str[0] == '+' || str[0] == '-') {
        str.erase(str.begin());
    }

    bool point = false;

    for (int i = 0; i < str.length(); i++) {
        if (str[i] - '0' < 0 || str[i] - '0' > 9) {
            if (str[i] == '.') {
                if (point) {
                    return false;
                }
                else {
                    point = true;
                }
            }
            else {
                return false;
            }
        }

    }

    return true;
}

bool isScientificNumber(std::string str) {
    std::string n = "";

    bool e = false;

    for (int i = 0; i < str.length(); i++) {
        n += str[i];
        if (!e && str[i] == 'e') {

            n.erase(i);
            e = true;

            if (!isDecimalNumber(n)) {
                return false;
            }

            n = "";

        }
    }

    if (e) {
        return (n == "") ? false : isIntNumber(n);
    }
    else {
        return isDecimalNumber(n);
    }
}
