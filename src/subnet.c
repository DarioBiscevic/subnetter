#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

#include "net.h"
#include "subnet.h"

unsigned int calculate_necessary_bits(unsigned int n_hosts){
    int n = n_hosts;
    unsigned int count = 0;

    while(n > 0){
        n /= 2;
        count++;
    }

    return count;
}

void print_list(subnet_t *list){
    subnet_t *el;
    if(list == NULL)
        printf("(empty)\n");
    else{
        el = list;
        while(el != NULL){
            printf("%s \t %d hosts \t %d bits \t ",
                el->name,
                el->n_hosts,
                el->bits);
            print_net(el->address);
            printf(" \t ");
            print_addr(el->broadcast_addr);
            printf("\n");
            el = el->next;
        }
    }
}

subnet_t *new_subnet(char * name, unsigned int n_hosts){
    subnet_t *new = malloc(sizeof(subnet_t));

    //Initialize the `name` field
    new->name = malloc(sizeof(char) * BUFFER_LEN);
    strcpy(new->name, name);

    new->n_hosts = n_hosts;
    new->bits = calculate_necessary_bits(n_hosts + 1);
    new->next = NULL;
    new->address = new_addr("0.0.0.0/0");
    new->broadcast_addr = 0;

    return new;
}

subnet_t *append(subnet_t *list, char * name, unsigned int n_hosts){
    if(list == NULL){
        //Return a new subnet as the new list
        return new_subnet(name, n_hosts);
    }

    if(list->next != NULL){
        list->next = append(list->next, name, n_hosts);
        return list;
    }

    //Create new subnet
    subnet_t *new =  new_subnet(name, n_hosts);
    new->next = NULL;

    //Add it to the tail of the list
    list->next = new;

    return list;
}

subnet_t *insert_in_order(subnet_t *list, char * name, unsigned int n_hosts){
    if(list == NULL){
        return new_subnet(name, n_hosts);
    }

    if(n_hosts > list->n_hosts){
        subnet_t *new = new_subnet(name, n_hosts);
        new->next = list;
        return new;
    }

    list->next = insert_in_order(list->next, name, n_hosts);

    return list;
}

int partition(subnet_t *list, net_t starting_address){

    if(list == NULL){
        return 0;
    }

    int nm_diff = 32 - list->bits - starting_address.netmask;

    if(nm_diff < 0){
        return 1;
    }

    subnet_t *el = list;

    unsigned int shift = pow(2, list->bits);
    unsigned int iters = pow(2, nm_diff);

    unsigned int i = 0;

    net_t new_net;
    /*
    * We can immediately set the netmask for this variable because it doesn't change
    * during the execution
    */
    new_net.netmask = starting_address.netmask + nm_diff;

    while(el != NULL && el->bits == list->bits && i < iters){
        new_net.address = starting_address.address + i * shift;

        el->address = new_net;
        el->broadcast_addr = new_net.address + shift - 1;

        el = el->next;
        i++;
    }

    int out = 0;
    while(i < iters && out == 0 && el != NULL){
        if(el->address.address == 0){
            new_net.address = starting_address.address + i * shift;

            out = partition(el, new_net);
            i++;
        }

        el = el->next;
    }
    
    return out;
}