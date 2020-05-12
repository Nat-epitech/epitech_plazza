#include "Order.h"
#include <thread>

std::mutex mtx;
std::ofstream outfile ("log");

int display_inventory(char *str, std::vector<int> *token)
{
    mesg_buffer message;

    if (strncmp(str, "status", 6))
        return (0);
    outfile << "Affichage des états des cuisines" << std::endl;
    message.mesg_type = 1;
    strcpy(message.mesg_text, "status");
    message.mesg_text[7] = '\0';
    mtx.lock();
    if ((int)token->size() == 0)
        std::cout << BLUE << "Aucune cuisine existante" << RESET << std::endl;
    for (int i = 0; i < (int)token->size(); i++){
        message.mesg_text[6] = i + 1;
        msgsnd(token->at(i), &message, sizeof(message), 0);
        usleep(10000);
    }
    mtx.unlock();
    return (1);
}

void main_command(char *input, int nb, std::vector<int> *token, int stock, float cook_time)
{
    Order(input, nb, token, stock, cook_time).main_loop();
    return;
}

void test_kitchen(std::vector<int> *token)
{
    mesg_buffer message;

    message.mesg_type = 1;
    while (1)
    {
        sleep(1);
        if ((int)token->size() <= 0)
            continue;
        for (int i = 0; i < (int)token->size(); i++){
            strcpy(message.mesg_text, "get_Status");
            msgsnd(token->at(i), &message, sizeof(message), 0);
            usleep(2000);
            msgrcv(token->at(i), &message, sizeof(message), 1, 0);
            if (!strcmp(message.mesg_text, "2")){
                msgctl(token->at(i), IPC_RMID, NULL);
                token->erase (token->begin()+i);
            }
        }
    }
}

int main(int ac, char **av)
{
    std::vector<int> token;
    char input[100];
    std::thread(test_kitchen, &token).detach();

    if (ac != 4 || std::atof(av[1]) < 0 || atoi(av[2]) <= 0 || atoi(av[3]) <= 0)
        return (84);
    system("clear");
	std::cout << CYAN << "\t\tBienvenue !" << RESET << std::endl;
    while (1)
    {
        //mtx.lock();
        std::cout << CYAN << " -> " << RESET << std::flush;
        if (!std::cin.getline(input,sizeof(input))){
            std::cout << std::endl;
            break;
        }
        //mtx.unlock();
        if (display_inventory(input, &token))
            continue;
        std::thread(main_command, input, atoi(av[2]), &token, atoi(av[3]), atof(av[1])).detach();
    }
    return (0);
}