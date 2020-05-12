/*
** EPITECH PROJECT, 2019
** CCP_plazza_2019
** File description:
** order.cpp
*/

#include "Order.h"
#include "Kitchen.h"

Order::Order(char *orderLine, int nb, std::vector<int> *kitchen_id, int restock_time, float cook_time)
{
    _save = strdup(orderLine);
    _orderline = strdup(orderLine);
    _nb_cook = nb;
    _kitchen_id = kitchen_id;
    _restock_time = restock_time;
    _cook_time = cook_time;
}

Order::~Order() {}

void Order::add_pizzas(char *name, int nb)
{
    std::string pizza(name);

    for (int z = _splited_order.size(), i = 0; i < nb;) {
        _splited_order.push_back(pizza);
        _splited_order.at(z) += ' ';
        i++;
        for (int y = 1; y < _nb_cook * 2 && i < nb; y++, i++) {
            _splited_order.at(z) += pizza;
            if (y != _nb_cook -1)
                _splited_order.at(z) += ' ';
        }
        z++;
    }
}

void Order::pack(char *str)
{
    char **tab = checker(str_wordtab(str, ";"));
    char **final;
    int j = 0;
    int i;

    if (tab == NULL)
        return;
    while (tab[j] != NULL){
        final = str_wordtab(tab[j], " ");
        i = atoi(&final[2][1]);
        this->add_pizzas(final[0], i);
        for (int k = 0; final[k] != NULL; free(final[k++]));
        free (final);
        j++;
    }
}

void Order::add_kitchen(mesg_buffer *message, std::vector<int> *tmp)
{
    _kitchen_id->push_back(msgget(IPC_PRIVATE, 0666 | IPC_CREAT));
    int pid = fork();
    if (pid == 0)
        Kitchen(_kitchen_id->at((int)_kitchen_id->size() - 1), _nb_cook, _restock_time, _cook_time).main_loop();
    msgsnd(_kitchen_id->at((int)_kitchen_id->size() - 1), message, sizeof(*message), 0);
    tmp->push_back(_kitchen_id->at((int)_kitchen_id->size() - 1));
}

void Order::main_loop()
{
    mesg_buffer message;
    int j = 0;
    std::vector<int> tmp;

    this->pack(_orderline);
    if ((int)_splited_order.size() == 0)
        return;
    outfile << "Acceptation de la commande : " << _save << std::endl;
    message.mesg_type = 1;
    for (int i = 0; i < (int)_kitchen_id->size() && j < (int)_splited_order.size(); i++){
        strcpy(message.mesg_text, "get_Status");
        msgsnd(_kitchen_id->at(i), &message, sizeof(message), 0);
        usleep(2000);
        msgrcv(_kitchen_id->at(i), &message, sizeof(message), 1, 0);
        if (!strcmp(message.mesg_text, "0")){
            strcpy(message.mesg_text, _splited_order.at(j).c_str());
            j++;
            msgsnd(_kitchen_id->at(i), &message, sizeof(message), 0);
            tmp.push_back(_kitchen_id->at(i));
        }
    }
    mtx.lock();
    if (j < (int)_splited_order.size())
        outfile << "Ouverture de " << (int)_splited_order.size() - j << " nouvelle(s) cuisine(s)" << std::endl;
    mtx.unlock();
    for (; j < (int)_splited_order.size(); j++){
        strcpy(message.mesg_text, _splited_order.at(j).c_str());
        this->add_kitchen(&message, &tmp);
    }
    for (int k = 0; k < (int)tmp.size();){
        strcpy(message.mesg_text, "get_Status");
        msgsnd(tmp.at(k), &message, sizeof(message), 0);
        usleep(2000);
        msgrcv(tmp.at(k), &message, sizeof(message), 1, 0);
        if (!strcmp(message.mesg_text, "0"))
            k++;
        usleep(2000);
    }
    mtx.lock();
    outfile << "Commande : " << _save << " -> finie avec " << (int)_splited_order.size() << " cuisine(s)" << std::endl;
    std::cout << GREEN << "Commande : " << _save << " -> finie avec " << (int)_splited_order.size() << " cuisine(s)" << std::endl << CYAN << " -> " << RESET << std::flush;
    mtx.unlock();
}