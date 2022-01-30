#undef UNICODE

#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>

//_beginthreadex() (#include <process.h>):
//The _beginthreadex() function creates a new thread, and returns a handle to the new thread. allows for multi threading
#include <process.h>

// Need to link with Ws2_32.lib
#pragma comment(lib, "Ws2_32.lib")

#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "27015"
int zero = 0;
int __cdecl main(void)
{

    WSADATA wsaData;
    //iResult is used repeatedly to store error codes. Value is determined by stage in code but should usually be 0
    int iResult;

    SOCKET ListenSocket = INVALID_SOCKET;
    SOCKET ClientSocket = INVALID_SOCKET;

    struct addrinfo *result = NULL;
    struct addrinfo hints;

    int iSendResult;
    char recvbuf[DEFAULT_BUFLEN];
    int recvbuflen = DEFAULT_BUFLEN;

    // Initialize Winsock
    iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0)
    {
        printf("WSAStartup failed with error: %d\n", iResult);
        return 1;
    }
    //fills hints with zeros but allocates memory based on the size of each type in the struct
    ZeroMemory(&hints, sizeof(hints));
    //fill addr info into hints
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    hints.ai_flags = AI_PASSIVE;

    // Resolve the server address and port, NULL is for nodename and service is for port
    //check if hints can be matched into result for use in a socket
    iResult = getaddrinfo(NULL, DEFAULT_PORT, &hints, &result);
    if (iResult != 0)
    {
        printf("getaddrinfo failed with error: %d\n", iResult);
        WSACleanup();
        return 1;
    }

    // Create a SOCKET for connecting to server
    ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
    if (ListenSocket == INVALID_SOCKET)
    {
        printf("socket failed with error: %ld\n", WSAGetLastError());
        //clears result from memory
        freeaddrinfo(result);
        WSACleanup();
        return 1;
    }

    // Setup the TCP listening socket
    //ai_addr is a struct that contains the address of the socket, ai_next is the next socket(or packet) in a list to be sent. must be manually set to use
    iResult = bind(ListenSocket, result->ai_addr, (int)result->ai_addrlen);
    if (iResult == SOCKET_ERROR)
    {
        printf("bind failed with error: %d\n", WSAGetLastError());
        freeaddrinfo(result);
        closesocket(ListenSocket);
        WSACleanup();
        return 1;
    }
    //clear result after socket has been bound to port
    freeaddrinfo(result);
    //listen is nonblocking however accept is blocking. After listen this should be pushed  to a new thread
    iResult = listen(ListenSocket, SOMAXCONN);
    if (iResult == SOCKET_ERROR)
    {
        printf("listen failed with error: %d\n", WSAGetLastError());
        closesocket(ListenSocket);
        WSACleanup();
        return 1;
    }

    
    // Accept a client socket
    ClientSocket = accept(ListenSocket, NULL, NULL);
    if (ClientSocket == INVALID_SOCKET)
    {
        printf("accept failed with error: %d\n", WSAGetLastError());
        closesocket(ListenSocket);
        WSACleanup();
        return 1;
    }

    // No longer need server socket
    //client socket has been accepted and is now connected to the client
    closesocket(ListenSocket);
    // Receive until the peer shuts down the connection
    do
    {   
        //this loop echos the message back to the client 
        //recv returns the length of the received data win bytes
        //get the respone from the client sock and push the value onto the recvbuf char array, recvbuflen is the length of the buffer and flags(0) is not needed for this application
        iResult = recv(ClientSocket, recvbuf, recvbuflen, 0);
        zero++;
        printf("%d\n", zero);
        //check if the recv was successful
        if (iResult > 0)
        {   
            
            printf("Bytes received: %d\n", iResult);
            printf("Received: %s\n", recvbuf);
            // Echo the buffer back to the sender, send returns the number of bytes sent
            iSendResult = send(ClientSocket, recvbuf, iResult, 0);
            if (iSendResult == SOCKET_ERROR)
            {
                //if error drop socket and close WinSock
                printf("send failed with error: %d\n", WSAGetLastError());
                closesocket(ClientSocket);
                WSACleanup();
                return 1;
            }
            //echo success1
            printf("Bytes sent: %d\n", iSendResult);
        }
        else if (iResult == 0)
        //if the recv was successful but no data was recieved
            printf("Connection closing...\n");
        else
        {
            printf("recv failed with error: %d\n", WSAGetLastError());
            closesocket(ClientSocket);
            WSACleanup();
            return 1;
        }

    } while (iResult > 0);

    // shutdown the connection since we're done, SD_send only kills send ops, we can still recieve data on the socket. SD=ShutDown
    iResult = shutdown(ClientSocket, SD_SEND);
    if (iResult == SOCKET_ERROR)
    {
        printf("shutdown failed with error: %d\n", WSAGetLastError());
        closesocket(ClientSocket);
        WSACleanup();
        return 1;
    }

    // cleanup
    closesocket(ClientSocket);
    WSACleanup();

    return 0;
}
