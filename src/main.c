#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <memory.h>
#include <wait.h>

#include "cgit.h"

int main(int argc, char **argv) {
    if (argc > 2 && strcmp(argv[1], "clone") == 0)
        return cgit_clone(argc, argv);
    else if (argc > 2 && strcmp(argv[1], "pull") == 0)
        return cgit_pull(argc, argv);
    else
        return execv(get_git_file(), argv);
}
