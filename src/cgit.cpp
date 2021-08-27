#include "cgit.hpp"

#include <memory.h>
#include <iostream>
#include <sstream>

#include "utils.hpp"

#ifdef WIN32
#define DEFAULT_GIT_FILE "C:\\Program Files\\Git\\bin\\git.exe"
#else
#define DEFAULT_GIT_FILE "/usr/bin/git"
#endif

#define DEFAULT_GITHUB_URL "https://github.com/"
#define DEFAULT_MIRROR_URL "https://github.com.cnpmjs.org/"

namespace cgit {
    using namespace std;

    static string create_cmd(std::vector<string> &args) {
        std::ostringstream ss;
        for (const auto &s:args) {
#ifdef WIN32
            ss << s << " ";
#else
            ss << "\"" << s << "\" ";
#endif
        }
        return ss.str();
    }

    string get_git_file() {
        auto git = get_env("GIT", DEFAULT_GIT_FILE);
        if (git == nullptr) {
            printf("please set the environment variable `GIT`.");
            exit(-1);
        }

        string git_str(git);
        if (git_str[0] != '"') git_str = '"' + git_str + '"';

        return git_str;
    }

    string get_cgit_mirror() {
        string url = get_env("CGIT_MIRROR", DEFAULT_MIRROR_URL);
        if (url.length() > 0 && !url.endswith("/"))url += '/';
        return url;
    }

    int cgit_clone(vector<string> &args) {
        // 0.get env for GIT and CGIT_MIRROR
        string git_file = get_git_file();
        string mirror_url = get_cgit_mirror();

        // 1.git clone https://github.com.cnpmjs.org/killf/cgit.git
        string old_url, new_url, folder_name;
        for (size_t i = 2; i < args.size(); i++) {
            if (args[i].startsWith(DEFAULT_GITHUB_URL)) {
                old_url = args[i];
                new_url = args[i].replace(0, strlen(DEFAULT_GITHUB_URL), mirror_url.c_str());

                auto index = old_url.find_last_of('/');
                if (index != std::string::npos) {
                    folder_name = old_url.substr(index + 1);
                    if (folder_name.endswith(".git")) {
                        folder_name = folder_name.substr(0, folder_name.size() - 4);
                    }
                }
            }
        }

        args[0] = git_file.c_str();
        auto cmd1 = create_cmd(args);
        auto err = system(cmd1.c_str());
        if (err != 0 || new_url.empty() || folder_name.empty())return err;

        // 2.cd cgit
        err = cd(folder_name);
        if (err != 0)return err;

        // 3.git remote set-url origin https://github.com/killf/cgit.git
        auto cmd3 = "git remote set-url origin \"" + old_url + "\"";
        return system(cmd3.c_str());
    }
}
