#ifndef SUBNET_H
#define SUBNET_H

#include <net.h>

#define BUFFER_LEN 256

typedef struct subnet_s {
    char *name;
    unsigned int n_hosts;
    unsigned int bits;
    net_t address;
    unsigned int broadcast_addr;
    struct subnet_s *next;
} subnet_t;

unsigned int calculate_necessary_bits(unsigned int);

void print_list(subnet_t *);

subnet_t *new_subnet(char *, unsigned int);

subnet_t *insert_in_order(subnet_t *, char *, unsigned int);

int partition(subnet_t *, net_t);

bool is_duplicate(char *, subnet_t *);

#endif