#ifndef CGIT_STRING_HPP
#define CGIT_STRING_HPP

#include <string>

namespace cgit {
    class string : public std::string {
    public:
        string() : std::string() {}

        string(const string &s) : std::string(s) {}

        string(const char *s) : std::string(s) {}

        string(const std::string &s) : std::string(s) {}

        string operator()(int n, int m) {
            return substr(n, m);
        }

        bool startsWith(const string &prefix) {
            if (this->size() < prefix.size())return false;

            const char *p1 = this->c_str();
            const char *p2 = prefix.c_str();

            while (*p2 != 0) {
                if (*p2++ != *p1++)return false;
            }

            return true;
        }

        bool endswith(const string &suffix) {
            if (this->size() < suffix.size())return false;

            const char *s = this->c_str() + (this->size() - suffix.size());
            return suffix == s;
        }
    };
}

#endif //CGIT_STRING_HPP
