#include "Kitchen.h"
#include "Order.h"

Kitchen::Kitchen(int token, int cooks_nb, int restock, float cook_time)
{
    _ingreds = (int *)malloc(sizeof(int) * 9);
    for (int i = 0; i < 9; _ingreds[i++] = 5)
    _token = token;
    _cooks_nb = cooks_nb;
    _cook_time = cook_time;
    _restock = restock;
    _status = 0;
    _timer = 0;
}

Kitchen::~Kitchen(){}

void Kitchen::display_inventory(int id)
{
    std::cout << BLUE << "  Kitchen " << id << " :\n\tDoe : " << _ingreds[0] << "\n\tTomato : " << _ingreds[1] << "\n\tGruyere : " << _ingreds[2] \
<< "\n\tHam : " << _ingreds[3] << "\n\tMushroom : " << _ingreds[4] << "\n\tSteak : " << _ingreds[5] << "\n\tEggplant : " << _ingreds[6]  \
<< "\n\tGoat cheese : " << _ingreds[7] << "\n\tChief love : " << _ingreds[8] << std::endl;
    std::cout << "\tEtat : " << (_status == 1 ? "\033[1;31moccupé" : "\033[1m\033[32minactive") << RESET << std::endl;
}

void Kitchen::loop_restock()
{
    while (1){
        usleep(_restock * 1000);
        for (int i = 0; i < 9; i++){
            if (_ingreds[i] < 5)
                _ingreds[i]++;
        }
    }
}

void Kitchen::cooking(char const *str, char const *two, int j)
{
    std::vector<int> miam = checkorder(str);
    char pizzas[4][10] = {"Margarita", "Regina", "Americana", "Fantasia"};
    int all_time[4] = {1, 2, 2, 4};
    int i = 0;

    for (i = 0; !strcasecmp(str, pizzas[i]); i++);
    for (long unsigned int i = 0; i < miam.size(); i++) {
        if (_ingreds[miam.at(i)] <= 0)
            sleep(_restock);
        _ingreds[miam.at(i)] -= 1;
    }
    sleep (all_time[i] * _cook_time);
    if (two != NULL && j == 0)
        this->cooking(two, str, 1);
}

void Kitchen::unpack(char **pizzas)
{
    int i;

    _timer = 0;
    _status = 1;
    for (i = 0; pizzas[i] != NULL; i++);
    std::thread cookers[i];
    for (int j = 0; j < i; j++)
        cookers[j] = std::thread([=]{cooking(pizzas[j], pizzas[j + 1], 0);});
    for (int j = 0; j < i; j++)
        cookers[j].join();
    _timer = 0;
    _status = 0;
}

void Kitchen::test_status()
{
    while (_timer < 5){
        sleep (1);
        _timer = (_status == 0 ? _timer + 1 : 0);
    }
    _status = 2;
}

void Kitchen::main_loop()
{
    mesg_buffer message;
    std::thread first (&Kitchen::loop_restock, this);
    std::thread second (&Kitchen::test_status, this);   

    while (msgrcv(_token, &message, sizeof(message), 1, 0) > 0){
        if (!strcmp(message.mesg_text, "get_Status")){
            message.mesg_text[0] = _status + 48;
            message.mesg_text[1] = '\0';
            msgsnd(_token, &message, sizeof(message), 0);
            usleep(2000);
        }
        else if (!strncmp(message.mesg_text, "status", 6))
            this->display_inventory(message.mesg_text[6]);
        else if (_status == 0 && strlen(message.mesg_text) > 5)
            std::thread([=]{unpack(str_wordtab(strdup(message.mesg_text), "|"));}).detach();
        usleep(2000);
    }
    outfile << "Cuisine : " << _token << " supprimée" << std::endl;
    exit (0);
}