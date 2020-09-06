#ifndef CGIT_H
#define CGIT_H

#include <vector>
#include <map>

#include "string.hpp"

namespace cgit {
    const char *get_git_file();

    int cgit_clone(std::vector<string> &argv);

    //int cgit_pull(int argc, char **argv);
}

#endif //CGIT_H
