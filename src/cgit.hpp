#ifndef CGIT_H
#define CGIT_H

#include <vector>
#include <map>

#include "string.hpp"

namespace cgit {
    string get_git_file();

    int cgit_clone(std::vector<string> &argv);
}

#endif //CGIT_H
