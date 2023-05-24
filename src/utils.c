#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <regex.h>

#include "subnet.h"
#include "utils.h"

void read_trimmed(char *buffer, unsigned int len){
    fgets(buffer, BUFFER_LEN, stdin);
    trim(buffer);
}

bool is_addr_valid(char *addr){
    regex_t regex;
    int reti;
    char msgbuf[100];
    bool res;

    /* Compile regular expression */
    reti = regcomp(&regex, "[0-9]*\\.[0-9]*\\.[0-9]*\\.[0-9]*/[0-9]*", 0);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        exit(1);
    }

    /* Execute regular expression */
    reti = regexec(&regex, addr, 0, NULL, 0);
    if (!reti)
        res = true;
    else if (reti == REG_NOMATCH) {
        printf("\t=> Invalid addr\n");
        res = false;
    }
    else {
        regerror(reti, &regex, msgbuf, sizeof(msgbuf));
        fprintf(stderr, "Regex match failed: %s\n", msgbuf);
        exit(1);
    }

    /* Free memory allocated to the pattern buffer by regcomp() */
    regfree(&regex);

    return res;
}

void trim(char *s){
    int i;
    for(i = 0; s[i] != '\0'; i++){
        if(s[i] == '\n')
            s[i] = '\0';
    }
}

