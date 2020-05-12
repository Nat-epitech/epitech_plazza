/*
** EPITECH PROJECT, 2019
** CCP_plazza_2019
** File description:
** Order.h
*/

#ifndef ORDER_HH_H
#define ORDER_HH_H

#include "my.h"
extern std::mutex mtx;
extern std::ofstream outfile;

class Order
{
    private:
        char *_save;
        char *_orderline;
        int _nb_cook;
        std::vector<int> *_kitchen_id;
        std::vector<std::string> _splited_order;
        int _restock_time;
        float _cook_time;
    public:
        Order(char *, int, std::vector<int> *, int, float);
        ~Order();
        void main_loop();
        void pack(char *str);
        void add_pizzas(char *name, int nb);
        void add_kitchen(mesg_buffer *message, std::vector<int> *tmp);
};

#endif