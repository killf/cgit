#include "cgit.h"

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <memory.h>

#define DEFAULT_GIT_FILE "/usr/bin/git"
#define DEFAULT_GITHUB_URL "https://github.com/"
#define DEFAULT_MIRROR_URL "https://github.com.cnpmjs.org/"

static int startswith(const char *s, const char *prefix) {
    if (strlen(s) < strlen(prefix))return 0;

    while (*prefix != 0) {
        if (*s == 0 || *prefix++ != *s++)return 0;
    }

    return 1;
}

static int endswith(const char *s, const char *suffix) {
    unsigned long l1 = strlen(s);
    unsigned long l2 = strlen(suffix);
    if (l1 < l2)return 0;

    s = s + (l1 - l2);
    return strcmp(s, suffix) == 0;
}

static const char *str_end(const char *s) {
    while (*s != 0)s++;
    return s;
}

static char *create_cmd(int argc, char **argv) {
    size_t capacity = 1024, size = 0;
    char *cmd = malloc(sizeof(char) * capacity);

    for (int i = 0; i < argc; i++) {
        while (size + strlen(argv[i]) > capacity) {
            capacity = capacity * 2;
            cmd = realloc(cmd, sizeof(char) * capacity);
        }

        size += sprintf(cmd + size, "\"%s\" ", argv[i]);
    }

    return cmd;
}

const char *get_git_file() {
    char *file = getenv("GIT");
    return file ? file : DEFAULT_GIT_FILE;
}

int cgit_clone(int argc, char **argv) {
    // 1.git clone https://github.com.cnpmjs.org/killf/cgit.git
    char *old_url = NULL, *new_url = NULL, *folder_name = NULL;
    for (int i = 2; i < argc; i++) {
        if (startswith(argv[i], DEFAULT_GITHUB_URL)) {
            old_url = argv[i];
            new_url = malloc(sizeof(char) * (strlen(old_url) + 16));
            sprintf(new_url, "%s%s", DEFAULT_MIRROR_URL, old_url + sizeof(DEFAULT_GITHUB_URL) - 1);
            argv[i] = new_url;

            char *end_ptr = strchr(old_url, '\0');
            if (endswith(old_url, ".git")) end_ptr -= 4;

            char *begin_ptr = strrchr(old_url, '/') + 1;

            folder_name = malloc(end_ptr - begin_ptr);
            strncpy(folder_name, begin_ptr, end_ptr - begin_ptr);
            break;
        }
    }

    argv[0] = (char *) get_git_file();
    char *cmd1 = create_cmd(argc, argv);
    int err = system(cmd1);
    if (err != 0 || new_url == NULL || folder_name == NULL)return err;

    // 2.cd cgit
    err = chdir(folder_name);
    if (err != 0)return err;

    // 3.git remote set-url origin https://github.com/killf/cgit.git
    char *cmd3 = malloc(sizeof(old_url) + 32);
    sprintf(cmd3, "git remote set-url origin \"%s\"", old_url);
    err = system(cmd3);

    // 4.free the memory
    free(cmd1);
    free(cmd3);
    free(new_url);
    free(folder_name);

    return err;
}

int cgit_pull(int argc, char **argv) {

    return 0;
}