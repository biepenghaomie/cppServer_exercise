#include<bits/stdc++.h>
#include<winsock2.h>
#pragma comment(lib,"ws2.lib")

const int maxn = 10000;
int main(){
    WSADATA wsaData;
    WORD wVersion = MAKEWORD(2, 2);
    if(WSAStartup(wVersion, &wsaData)){
        printf("WSAStartup\n");
    }

    SOCKET sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    sockaddr_in sockAddr;
    memset(&sockAddr, 0, sizeof(sockAddr));

    sockAddr.sin_family = AF_INET;
    sockAddr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
    sockAddr.sin_port = htons(8899);

    int flag = connect(sock, (sockaddr *)&sockAddr, sizeof(sockAddr));
    if(flag){
        printf("success connect\n");
    }
    while(1){
        char s[maxn] = { 0 };
        std::cin >> s;
        int flag = sendto(sock, s, strlen(s), true, (sockaddr *)&sockAddr, strlen(s));
        if(flag){
            break;
        }
    }
    closesocket(sock);
}