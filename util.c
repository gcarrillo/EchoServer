//
//  util.c
//  EchoServer
//
//  Created by Gabriel Carrillo on 2/26/16.
//  Copyright © 2016 Gabriel Carrillo. All rights reserved.
//

#include "util.h"
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#define MAXLINE 512

int readn(int fd, char *ptr, int nbytes) {
    int nleft, nread;
    
    nleft = nbytes;
    while (nleft > 0) {
        nread = (int)read(fd, ptr, nleft);
        if (nread < 0) {
            return(nread);
        } else if (nread == 0) {
            break;
        }
        
        nleft -= nread;
        ptr += nread;
    }
    
    return(nbytes - nleft);
}

int writen(int fd, char *ptr, int nbytes) {
    int nleft, nwritten;
    
    nleft = nbytes;
    
    while (nleft > 0) {
        nwritten = (int)write(fd, ptr, nleft);
        if (nwritten <= 0) {
            return(nwritten);
        }
        
        nleft -= nwritten;
        ptr += nwritten;
    }
    
    return(nbytes - nleft);
}

int readline(int fd, char *ptr, int maxlen) {
    int n, rc;
    char c;
    
    for (n = 1; n < maxlen; n++) {
        if ((rc = (int)read(fd, &c, 1)) == 1) {
            *ptr++ = c;
            
            if (c == '\n') break;
            
        } else if (rc == 0) {
            if (n == 1) {
                return 0;
            } else {
                break;
            }
        } else {
            return -1;
        }
    }
    
    *ptr = 0;
    
    return n;
}

void str_echo(int sockfd) {
    int n;
    char line[MAXLINE];
    
    for ( ; ; ) {
        n = readline(sockfd, line, MAXLINE);
        if (n == 0) {
            return;
        } else if (n < 0) {
            // Handle error
            fprintf(stderr, "str_echo: readline error");
            exit(-1);
        }
        
        if (writen(sockfd, line, n) != n) {
            // Handle error
            fprintf(stderr, "str_echo: writen error");
            exit(-1);
        }
    }
}

void str_cli(FILE *fp, int sockfd) {
    int n;
    char sendline[MAXLINE], recvline[MAXLINE + 1];
    
    while (fgets(sendline, MAXLINE, fp) != NULL) {
        n = (int)strlen(sendline);
        if (writen(sockfd, sendline, n) != n) {
            fprintf(stderr, "str_cli: writen error on socket");
            exit(-1);
        }
        
        /*
         * Now read a line from the socket and write it to
         * our standard output.
         */
        n = readline(sockfd, recvline, MAXLINE);
        if (n < 0) {
            fprintf(stderr, "str_cli: readline error");
            exit(-1);
        }
        
        recvline[n] = 0;
        fputs(recvline, stdout);
    }
    
    if (ferror(fp)) {
        fprintf(stderr, "str_cli: error reading file");
        exit(-1);
    }
}