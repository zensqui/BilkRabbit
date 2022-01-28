#include <stdio.h>  //for printf
#include <string.h> //memset
#include <stdlib.h> //for exit(0);
#include <errno.h>  //For errno - the error number

//!windows header
#include <winsock2.h>
#include <io.h>

// //! these are all unix headers
// #include <sys/socket.h>
// #include <netinet/tcp.hc>	//Provides declarations for tcp header
// #include <netinet/ip.h>	//Provides declarations for ip header
// #include <arpa/inet.h> // inet_addr
// #include <unistd.h> // sleep()

int main(void)
{
    //
    int s = socket(AF_INET, SOCK_RAW, IPPROTO_TCP);
    
    //print s to the console
    printf("socket: %d\n", s);
}