#include <unistd.h>
#include <vector>

#include "string.hpp"
#include "cgit.hpp"

using namespace cgit;

int main(int argc, char **argv) {
    std::vector<string> args(argc);
    for (int i = 0; i < argc; i++) {
        args[i] = argv[i];
    }

    if (argc > 2 && args[1] == "clone")
        return cgit_clone(args);
    else
        return execv(get_git_file(), argv);
}
