#include <iostream>
#include <thread> 
#include <vector>

#ifndef KITCHEN_HH_H
#define KITCHEN_HH_H

class	Kitchen
{
private:
    int _token;
    int _cooks_nb;
    float _cook_time;
    int _status;
    float _restock;
    int *_ingreds;
    int _timer;
public:
  Kitchen(int, int, int, float);
  ~Kitchen();
  void display_inventory(int id);
  void main_loop();
  void unpack(char **pizzas);
  void cooking(char const *str);
  void loop_restock();
  void test_status();
  void cooking(char const *str, char const *two, int j);
};

#endif