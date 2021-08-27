#ifndef CGIT_UTILS_HPP
#define CGIT_UTILS_HPP

namespace cgit {
    const char *get_env(const char *name, const char *default_value);

    int exec(const string &file_name, char *const *arguments);

    int cd(const string &path);
}
#endif //CGIT_UTILS_HPP
