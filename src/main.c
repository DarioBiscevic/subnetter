#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <regex.h>

#include <subnet.h>
#include <utils.h>

#define ADDR_LEN 20
#define STOP_CHAR '\\'

int main(int argc, char *argv[]){
    int n;
    char name_buffer[BUFFER_LEN + 1];
    char host_buffer[BUFFER_LEN + 1];
    char addr_buffer[ADDR_LEN + 1];

    subnet_t *subnets = NULL;
    n = 0;

    //Read the first subnet
    do {
        printf("Subnet name: ");
        read_trimmed(name_buffer, BUFFER_LEN);
    }while(strlen(name_buffer) == 0);

    //Continue to get subnets until the stop character is given
    while(name_buffer[0] != STOP_CHAR){
        //Read the number of hosts for the specified subnet
        do {
            printf("# of hosts: ");
            read_trimmed(host_buffer, BUFFER_LEN);
        } while(strlen(host_buffer) == 0);

        //Insert the subnet in the list
        subnets = insert_in_order(subnets, name_buffer, atoi(host_buffer));
        n++;

        printf("\n");

        //Read further subnets and check if it's a duplicate
        bool is_dup = false;
        do {
            if(is_dup)
                printf("\t=> Duplicate subnet\n");
            printf("Subnet name: ");
            read_trimmed(name_buffer, BUFFER_LEN);
            is_dup = is_duplicate(name_buffer, subnets);
        }while(strlen(name_buffer) == 0 || is_dup);
    }

    printf("\n");

    //Read the starting address for the partitioning
    do {
        printf("Starting address: ");
        read_trimmed(addr_buffer, ADDR_LEN);
    }while(!is_addr_valid(addr_buffer));

    //Partition the subnet
    net_t starting_address = new_addr(addr_buffer);
    int res = partition(subnets, starting_address);

    if(res != 0)
        printf("An error occured during the partitioning process");
    else
        print_list(subnets);
    
    printf("\n");

    return res;
}
