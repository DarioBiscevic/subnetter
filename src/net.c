#include <stdio.h>

#include "net.h"

void print_addr(unsigned int addr){
    unsigned int dec[4];

    for(int i = 3; i >= 0; i--){
        dec[i] = addr % 256;
        addr /= 256;
    }

    for(int i = 0; i < 3; i++){
        printf("%d.", dec[i]);
    }

    printf("%d", dec[3]);
}

void print_net(net_t net){
    print_addr(net.address);

    printf("/%d", net.netmask);
}

net_t new_addr(char buffer[]){
    net_t addr;
    
    int i;
    int n = 0;
    addr.address = 0;
    for(i = 0; i < 4; i++){
        unsigned char val = 0;
        while(buffer[n] != '.' && buffer[n] != '/'){
            val *= 10;
            val += buffer[n] - '0';
            n++;
        }
        addr.address *= 256;
        addr.address += val;
        n++;
    }

    int netmask = 0;
    while(buffer[n] != '\0'){
        netmask *= 10;
        netmask += buffer[n] - '0';
        n++;
    }

    addr.netmask = netmask;

    return addr;
}