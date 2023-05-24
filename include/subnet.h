#ifndef SUBNET_H
#define SUBNET_H

#include "net.h"

#define BUFFER_LEN 256

typedef struct subnet_s {
    char *name;
    unsigned int n_hosts;
    unsigned int bits;
    net_t address;
    unsigned int broadcast_addr;
    struct subnet_s *next;
} subnet_t;

unsigned int calculate_necessary_bits(unsigned int n_hosts);
void print_list(subnet_t *list);
subnet_t *new_subnet(char * name, unsigned int n_hosts);
subnet_t *append(subnet_t *list, char * name, unsigned int n_hosts);
subnet_t *insert_in_order(subnet_t *list, char * name, unsigned int n_hosts);
int partition(subnet_t *list, net_t starting_address);

#endif