#ifndef NET_H
#define NET_H

typedef struct net_s {
    unsigned int address;
    unsigned char netmask;
} net_t;

void print_addr_dec(net_t net);
net_t new_addr(char buffer[]);

#endif