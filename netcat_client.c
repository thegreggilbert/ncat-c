/* *********************************************************************** *
 *
 *       Filename:  netcat_client.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  Thursday 07 March 2013 03:03:24  IST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Prakash Gamit (09211014), <prakashgamit23@gmail.com>
 *   Organization:  Indian Institute of Technology, Roorkee
 *
 * ********************************************************************* */

#include "netcat_client.h"
#include <netdb.h> // gethostbyname

int sockfd;


void start_client(){

    if(o.udp)
        sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    else
        sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if(sockfd == -1)
        die("socket");

    struct sockaddr_in servaddr;
    bzero(&servaddr, sizeof(servaddr));

    /////////////// hostname support ////////////////////////////
    struct hostent *hostent1 = gethostbyname(o.target);
    if(!hostent1)
    {
        bye("could't resolve hostname\n");
    }
    memcpy(&(servaddr.sin_addr), hostent1->h_addr_list[0], hostent1->h_length);
    /////////////////////////////////////////////////////////////

    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(o.port);

    // int status = inet_pton(AF_INET, o.target, &servaddr.sin_addr);
    // if(status == -1)
    //     die("inet_pton");
    // else if(status == 0){/* hostname given not IP */
    //     //TODO
    //     /* get IP from hostname
    //      * but for now print error and exit
    //      */
    //     bye("hostname not supported\ngive IP-address\n");
    // }

    if(connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) == -1)
        die("connect");

    if(o.verbose){
        printf("connected to (%s, %d)\n", o.target, o.port);
    }

    char sendline[MAX], recvline[MAX];
    
    fd_set rset;
    int maxfdp1;
    int bytes;

    FD_ZERO(&rset);
    while(1){
        FD_SET(fileno(stdin), &rset);
        FD_SET(sockfd, &rset);

        maxfdp1 = (fileno(stdin) < sockfd ? sockfd : fileno(stdin)) + 1;

        if(select(maxfdp1, &rset, NULL, NULL, NULL) == -1)
            die("select");

        if(FD_ISSET(sockfd, &rset)){
            bzero(recvline, MAX);
            bytes = read(sockfd, recvline, MAX);

            if(bytes == -1)
                die("read");
            else if(bytes == 0)
                break;

            fputs(recvline, stdout);
        }

        if(FD_ISSET(fileno(stdin), &rset)){
            bzero(sendline, MAX);
            bytes = read(fileno(stdin), sendline, MAX);

            if(bytes == -1)
                die("read");
            else if(bytes == 0)
                break;

            if(write(sockfd, sendline, strlen(sendline)) == -1)
                die("write");
        }
    }/* while */

    close(sockfd);
    if(o.verbose)
        printf("closed connection to (%s, %d)\n", o.target, o.port);
}/* start_client() */
