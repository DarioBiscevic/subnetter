#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <regex.h>

#include "subnet.h"
#include "utils.h"

#define ADDR_LEN 20
#define STOP_CHAR '\\'

int main(int argc, char *argv[]){
    int n;
    char name_buffer[BUFFER_LEN + 1];
    char host_buffer[BUFFER_LEN + 1];
    char addr_buffer[ADDR_LEN + 1];

    subnet_t *subnets = NULL;
    n = 0;

    do {
        printf("Subnet name: ");
        read_trimmed(name_buffer, BUFFER_LEN);
    }while(strlen(name_buffer) == 0);

    while(name_buffer[0] != '\\'){
        do {
            printf("# of hosts: ");
            read_trimmed(host_buffer, BUFFER_LEN);
        } while(strlen(host_buffer) == 0);

        subnets = insert_in_order(subnets, name_buffer, atoi(host_buffer));
        n++;

        printf("\n");

        do {
            printf("Subnet name: ");
            read_trimmed(name_buffer, BUFFER_LEN);
        }while(strlen(name_buffer) == 0);
    }

    do {
        printf("Starting address: ");
        read_trimmed(addr_buffer, ADDR_LEN);
    }while(!is_addr_valid(addr_buffer));

    net_t starting_address = new_addr(addr_buffer);

    int res = partition(subnets, starting_address);

    if(res != 0){
        printf("An error occured during the partitioning process\n");
    }else{
        print_list(subnets);
        printf("\n");
    }

    return res;
}
