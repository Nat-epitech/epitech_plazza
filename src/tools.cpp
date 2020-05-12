#include "my.h"
#include "Kitchen.h"

std::vector<int> checkorder(char const *str)
{
    std::vector<int> ret;

    if (!strcasecmp("Margarita", str)) {
        ret.push_back(0);
        ret.push_back(1);
        ret.push_back(2);
    }
    if (!strcasecmp("Regina", str)){
        ret.push_back(0);
        ret.push_back(1);
        ret.push_back(2);
        ret.push_back(3);
        ret.push_back(4);
    }
    if (!strcasecmp("Americana", str)) {
        ret.push_back(0);
        ret.push_back(1);
        ret.push_back(2);
        ret.push_back(5);
    }
    if (!strcasecmp("Fantasia", str)){
        ret.push_back(0);
        ret.push_back(1);
        ret.push_back(6);
        ret.push_back(7);
        ret.push_back(8);
    }
    return (ret);
}

char **checker(char **order)
{
    std::vector<std::string> checkit;
    std::istringstream ss;

    if (order == NULL)
        return (NULL);
    for (int i = 0; order[i]; i++) {
        std::string tmp_s(order[i]);
        checkit.push_back(tmp_s);
    }
    for (int i = 0; i < (int)checkit.size(); i++) {
        ss.str(checkit.at(i));
        std::string word;
        ss >> word;
        if (strcasecmp(word.c_str(), "regina") && strcasecmp(word.c_str(), "margarita") && strcasecmp(word.c_str(), "americana") && strcasecmp(word.c_str(), "fantasia")) {
            checkit.erase(checkit.begin() + i);
            i--;
            continue;
        }
        word.clear();
        ss >> word;
        if (strcasecmp(word.c_str(), "S") && strcasecmp(word.c_str(), "M") && strcasecmp(word.c_str(), "L") && strcasecmp(word.c_str(), "XL") && strcasecmp(word.c_str(), "XXL")) {
            checkit.erase(checkit.begin() + i);
            i--;
            continue;
        }
        word.clear();
        ss >> word;
        if (word[0] != 'x' && word[0] != 'X') {
            checkit.erase(checkit.begin() + i);
            i--;
            continue;
        }
        if (word[1] <= '0' || word[1] > '9') {
            checkit.erase(checkit.begin() + i);
            i--;
            continue;
        }
        for (size_t z = 2; word[z]; z++) {
            if (word[z] < '0' || word[z] > '9') {
                checkit.erase(checkit.begin() + z);
                i--;
                break;
            }
        }
        ss.clear();
    }
    char **ret = new char*[checkit.size()];
    for (int i = 0; i <= (int)checkit.size(); i++){
        if (i < (int)checkit.size())
            ret[i] = strdup(checkit.at(i).c_str());
        else
            ret[i] = NULL;
    }
    return (ret);
}

char **str_wordtab(char *str, char const *tok)
{
    int i = 0;
    char **tab = (char **)malloc(sizeof(char *));
    char *token = strtok(str, tok);

    if (!str || !tab || !token)
        return (NULL);
    while (token != NULL) {
        tab[i++] = strdup(token);
        tab = (char **)realloc(tab, (sizeof(char *) * (i + 1)));
        token = strtok(NULL, tok);
    }
    tab[i] = token;
    free(token);
    return (tab);
}