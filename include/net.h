#ifndef NET_H
#define NET_H

typedef struct net_s {
    unsigned int address;
    unsigned char netmask;
} net_t;

void print_addr(unsigned int);

void print_net(net_t);

net_t new_addr(char []);

#endif