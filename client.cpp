#include<bits/stdc++.h>
#include <unistd.h>
#include<winsock2.h>
#include <errproccess.h>
#pragma comment(lib,"ws2.lib")

const int maxn = 10000;
int main(){
    WSADATA wsaData;
    WORD wVersion = MAKEWORD(2, 2);
    if(WSAStartup(wVersion, &wsaData)){
        printf("WSAStartup\n");
    }

    SOCKET sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    Err::errCheck(sock == -1, "create sock failed");
    sockaddr_in sockAddr;
    memset(&sockAddr, 0, sizeof(sockAddr));

    sockAddr.sin_family = AF_INET;
    sockAddr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
    sockAddr.sin_port = htons(8899);

    Err::errCheck(connect(sock, (sockaddr *)&sockAddr, sizeof(sockAddr)) == -1, "connect faied");
    while(1){
        char s[maxn] = { 0 };
        std::cin >> s;
        int writeSize = 0;
        writeSize = write(sock, s, sizeof(s));
        Err::errCheck(writeSize == -1, "write failed");
    }
    closesocket(sock);
}