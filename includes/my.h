#include <sys/msg.h>
#include <unistd.h>
#include <string.h>
#include <vector>
#include <cstdlib>
#include <string>
#include <sstream>
#include <iostream>
#include <mutex>
#include <fstream>

#define BLUE "\033[1m\033[34m"
#define RESET "\033[0m"
#define GREEN "\033[1m\033[32m"
#define CYAN "\033[1m\033[36m"


std::vector<int> checkorder(char const *str);
char **str_wordtab(char *str, char const *tok);
char **checker(char **order);
struct mesg_buffer
{
    long mesg_type;
    char mesg_text[100];
};