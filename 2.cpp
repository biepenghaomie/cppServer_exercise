#include <bits/stdc++.h>
#include<string>
#include <winsock.h>
#pragma comment(lib,"ws2.lib")
// using namespace std;

// #define int long long

const int maxn = 10000;

int main()
{
    WSADATA wsaData;
    WORD wVersion = MAKEWORD(2, 2);
    if(WSAStartup(wVersion, &wsaData)){
        printf("WSAStartup\n");
    }

    SOCKET sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    sockaddr_in serverAddr;
    memset(&serverAddr, 0, sizeof(serverAddr));

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
    serverAddr.sin_port = htons(8899);

    bind(sock, (sockaddr *)&serverAddr, sizeof(serverAddr));

    listen(sock, 5);
    while(1){
        SOCKET client;
        sockaddr_in clientAddr;
        int socklen = sizeof(clientAddr);
        client = accept(sock, (sockaddr *)&clientAddr, &socklen);
        printf("new client sock:%d,which ip is %s,port is %d\n", client,
            inet_ntoa(clientAddr.sin_addr), ntohs(clientAddr.sin_port));
        char data[maxn];
        int ret = recv(client, data, 255, 0);
        if(ret){
            printf("%s\n", data);
        }

    }
    closesocket(sock);
    return 0;
}