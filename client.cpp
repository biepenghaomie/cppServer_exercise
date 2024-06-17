#include <bits/stdc++.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <errproccess.h>

const int maxn = 10000;
int main(){

    int sock = socket(AF_INET, SOCK_STREAM, 0);
    Err::errCheck(sock == -1, "create sock failed");
    struct sockaddr_in sockAddr;
    memset(&sockAddr, 0, sizeof(sockAddr));

    sockAddr.sin_family = AF_INET;
    sockAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    sockAddr.sin_port = htons(8899);

    Err::errCheck(connect(sock, (sockaddr *)&sockAddr, sizeof(sockAddr)) == -1, "connect faied");
    while(1){
        char s[maxn] = { 0 };
        std::cin >> s;
        int writeSize = write(sock, s, sizeof(s));
        if(writeSize == -1){
            printf("has been disconnect\n");
            break;
        }
        memset(s, 0, sizeof(s));
        int readSize = read(sock, s, sizeof(s));
        if(readSize > 0){
            printf("get message from server: %s\n", s);
        }
        else if(readSize == -1){
            printf("read error\n");
            break;
        }
        else if(readSize == 0){
            printf("has been disconnect\n");
            break;
        }

    }
    close(sock);
}