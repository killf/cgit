#ifndef CGIT_UTILS_HPP
#define CGIT_UTILS_HPP

#ifdef WIN32
#include <direct.h>
#include <process.h>
#else
#include <unistd.h>
#endif

#include "string.hpp"

namespace cgit {
#ifdef WIN32
    const char *get_env(const char *name, const char *default_value) {
        char *file = nullptr;
        size_t len;
        errno_t err = _dupenv_s(&file, &len, name);
        return err == 0 && file != nullptr ? file : default_value;
    }

    int exec(const string &file_name, char *const *arguments) {
        return _execv(file_name.c_str(), arguments);
    }

    int cd(const string &path) {
        return _chdir(path.c_str());
    }
#else
    const char *get_env(const char *name, const char *default_value) {
        char *file = getenv(name);
        return file ? file : default_value;
    }

    int exec(const string &file_name, char *const* arguments){
        return execv(file_name.c_str(), arguments);
    }

    int cd(const string &path) {
        return chdir(path.c_str());
    }
#endif
}
#endif //CGIT_UTILS_HPP
