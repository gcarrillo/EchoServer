//
//  main.c
//  Echo Server
//
//  Based on example from "UNIX Network Programming" by Stevens
//
//  Created by Gabriel Carrillo on 2/26/16.
//  Copyright © 2016 Gabriel Carrillo. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <unistd.h>
#include "inet.h"
#include "util.h"

int main(int argc, char * argv[]) {
    int sockfd, newsockfd, childpid;
    unsigned int clilen;
    struct sockaddr_in cli_addr, serv_addr;
    
    pname = argv[0];
    
    printf("Echo server running\n");
    
    /*
     * Open a TCP socket (an Internet stream socket).
     */
    
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        // Handle error
        fprintf(stderr, "server: can't open stream socket");
        exit(-1);
    }
    
    /*
     * Bind our local address so that the client can send to us.
     */
    bzero((char *)&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(SERV_TCP_PORT);
    
    if (bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        // Handle error
        fprintf(stderr, "server: can't bind local address");
        exit(-1);
    }
    
    listen(sockfd, 5);
    
    for ( ; ; ) {
        /*
         * Wait for a connection from a client process.
         * This is an example of a concurrent server.
         */
        
        clilen = sizeof(cli_addr);
        newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, &clilen);
        
        if (newsockfd < 0) {
            // Handle error
            fprintf(stderr, "server: accept error");
            exit(-1);
        }
        
        if ((childpid = fork()) < 0) {
            // Handle error
            fprintf(stderr, "server: fork error");
            exit(-1);
        } else if (childpid == 0) {
            // Child process
            close(sockfd);
            str_echo(newsockfd);
            exit(0);
        } else {
            // Parent process
            close(newsockfd);
        }
    }
    
    return 0;
}
