#ifndef CGIT_H
#define CGIT_H

const char *get_git_file();

int cgit_clone(int argc, char **argv);

int cgit_pull(int argc, char **argv);

#endif //CGIT_H
