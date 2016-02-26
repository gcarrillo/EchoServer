//
//  util.h
//  EchoServer
//
//  Created by Gabriel Carrillo on 2/26/16.
//  Copyright © 2016 Gabriel Carrillo. All rights reserved.
//

#ifndef util_h
#define util_h

#include <stdio.h>

int readn(int fd, char *ptr, int nbytes);
int writen(int fd, char *ptr, int nbytes);
int readline(int fd, char *ptr, int maxlen);
void str_echo(int sockfd);
void str_cli(FILE *fp, int sockfd);

#endif /* util_h */
