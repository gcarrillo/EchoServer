//
//  main.c
//  EchoClient
//
//  Created by Gabriel Carrillo on 2/26/16.
//  Copyright © 2016 Gabriel Carrillo. All rights reserved.
//

#include <stdio.h>
#include <strings.h>
#include <stdlib.h>
#include <unistd.h>

#include "inet.h"
#include "util.h"

int main(int argc, char * argv[]) {
    int sockfd;
    struct sockaddr_in serv_addr;
    
    pname = argv[0];
    
    /*
     * Fill in the structure "serv_addr" with the address of the
     * server that we want to connect with.
     */
    
    bzero((char *)&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(SERV_HOST_ADDR);
    serv_addr.sin_port = htons(SERV_TCP_PORT);
    
    /*
     * Open a TCP socket (an internet stream socket).
     */
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        // Handle error
        fprintf(stderr, "client: can't open stream socket");
        exit(-1);
    }
    
    /*
     * Connect to the server.
     */
    
    if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        // Handle error.
        fprintf(stderr, "client: can't connect to server.");
        exit(-1);
    }
    
    str_cli(stdin, sockfd);
    
    close(sockfd);
    
    return 0;
}
