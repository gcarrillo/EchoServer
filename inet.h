//
//  inet.h
//  EchoServer
//
//  Created by Gabriel Carrillo on 2/26/16.
//  Copyright © 2016 Gabriel Carrillo. All rights reserved.
//
//  Definitions for TCP and UDP client/server programs.

#ifndef inet_h
#define inet_h

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define SERV_TCP_PORT   6000
#define SERV_HOST_ADDR  "192.168.1.5"  /* host addr for server */

char    *pname;

#endif /* inet_h */
