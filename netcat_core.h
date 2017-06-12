/* *********************************************************************** *
 *       Filename:  netcat_core.h
 *
 *    Description:  define options struct & declare global variables
 *
 *        Version:  1.0
 *        Created:  Wednesday 06 March 2013 01:31:03  IST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Prakash Gamit (09211014), <prakashgamit23@gmail.com>
 *   Organization:  Indian Institute of Technology, Roorkee
 *
 * ********************************************************************** */

#ifndef _NETCAT_CORE_H_
#define _NETCAT_CORE_H_


/* include standar header files */
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#include <string.h>
#include <strings.h>

#include <unistd.h>
#include <errno.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <netinet/in.h>

// remove warnings for inet_aton and other similar functions
#include <arpa/inet.h>

#define MAX 1024


struct options{
    /* host to connect to in case of client mode */
    char *target;

    /* source port to use */
    unsigned short port;

    /* is it listen mode or client mode */
    int listen;
    /* accept multiple connections in listen mode */
    int keepopen;

    /* socket is udp */
    int udp;

    /* should be verbose */
    int verbose;

    /* command is to be executed */
    int execcommand;
    /* command to execute */
    char *command;
};


/* global options struct */
extern struct options o;


/* initialize options struct to default values */
extern void init_options(void);


/* print error message to @stderr and exit */
extern void bye(const char *, ...);


/* writes error message using perror and then quits */
extern void die(char *);


#endif
