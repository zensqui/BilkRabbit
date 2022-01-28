#include <stdio.h>  //for printf
#include <string.h> //memset
#include <stdlib.h> //for exit(0);
#include <errno.h>  //For errno - the error number
#include <stdint.h> //for numbers and such

//
#include "checksum.h"

//! Windows headers
//#include <WinSock.h>
#include <winsock2.h>
#include <io.h>

// //! these are all unix headers
// #include <sys/socket.h>
// #include <netinet/tcp.hc>	//Provides declarations for tcp header
// #include <netinet/ip.h>	//Provides declarations for ip header
// #include <arpa/inet.h> // inet_addr
// #include <unistd.h> // sleep()

struct pseudo_header
{
    uint32_t source_address;
    uint32_t dest_address;
    uint8_t placeholder;
    uint8_t protocol;
    uint16_t tcp_length;
};

int main(void)
{
    WORD wVersionRequested;
    WSADATA wsaData;
    int err;

    /* Use the MAKEWORD(lowbyte, highbyte) macro declared in Windef.h */
    wVersionRequested = MAKEWORD(2, 2);

    err = WSAStartup(wVersionRequested, &wsaData);

    //
    int s = socket(AF_INET, SOCK_RAW, IPPROTO_TCP);
    if (s == -1)
    {
        //socket creation failed, may be because of non-root privileges
        perror("Failed to create socket\n");
        exit(1);
    }

    //print s to the console
    printf("socket: %d\n", s);
}